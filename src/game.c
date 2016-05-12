#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "game.h"
#include "physics.h"

// Global variables
bool quit = false;
SDL_Event event;
unsigned int tick = 0;

// Surfaces
SDL_Surface *screen = NULL;

int main(int argc, char** argv) {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT,
            SCREEN_BPP, SDL_SWSURFACE);

#ifdef TEST_SDL_LOCK_OPTS
    EM_ASM("SDL.defaults.copyOnLock = false; SDL.defaults.discardOnLock = true; SDL.defaults.opaqueFrontBuffer = false;");
#endif


    printf("Setting up main loop\n");

    srand(time(NULL));

    for (int i=0; i<50; i++) {
        printf("Adding a projectile.\n");
        // get random x, y, vx, vy
        add_projectile(
            rand() % SCREEN_WIDTH,
            rand() % SCREEN_HEIGHT,
            rand() % 20 - 10,
            rand() % 20 - 10,
            20);
    }

    // Add a big one
    add_projectile(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0, 0, 100);

/*
    add_projectile(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 - 20, 0, 0, 20);
    add_projectile(SCREEN_WIDTH, SCREEN_HEIGHT/2 + 20, -2, 0, 20);
*/


    emscripten_set_main_loop(game_tick, 0, 1);

    return 0;
}

void game_tick() {

    tick++;

    physics_tick();

    //While there's an event to handle
    while( SDL_PollEvent( &event ) )
    {
        //If a key was pressed
        if( event.type == SDL_KEYDOWN )
        {
        }

    }

    //if (SDL_MUSTLOCK(screen)) SDL_LockSurface(screen);

    //
    // Draw background
    //
    SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 0, 0, 0, 255));

    //
    // Draw projectiles
    //
    
    for (int i=0; i<get_num_projectiles(); i++) {
        struct projectile *p = get_projectile(i);

        //printf("rect: %d, %d, %d, %d\n", rect.x, rect.y, rect.w, rect.h);
        int d = (int) sqrt(p->diam);
        int x = p->x - d/2;
        int y = p->y - d/2;

        SDL_Rect rect = {x, y, d, d};

        SDL_FillRect(screen, &rect, SDL_MapRGBA(screen->format, 255, 0, 0, 255));
    }

    //if (SDL_MUSTLOCK(screen)) SDL_UnlockSurface(screen);

    SDL_Flip(screen); 
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}
