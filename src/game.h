#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <unistd.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 600
#define SCREEN_BPP 32
#define FPS 15

// Prototypes
void game_tick();
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);

#endif
