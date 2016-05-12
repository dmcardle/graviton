#include <math.h>

#include "game.h"
#include "physics.h"

#define MAX_PROJECTILES 1000

static struct projectile projectile[MAX_PROJECTILES];
static int num_projectiles = 0;

struct projectile* get_projectile(int i) {
    return &projectile[i];
}
int get_num_projectiles() {
    return num_projectiles;
}

void add_projectile(double x, double y, double vx, double vy, double mass) {
    if (num_projectiles >= MAX_PROJECTILES) {
        printf("Too many projectiles!\n");
        return;
    }

    struct projectile *p = get_projectile(num_projectiles);
    num_projectiles++;

    p->x = x;
    p->y = y;
    p->vx = vx;
    p->vy = vy;
    p->mass = mass;
    p->diam = (int)mass;
}

void physics_tick() {
    for (int i=0; i<num_projectiles; i++) {
        struct projectile *p = get_projectile(i);

        p->lastX = p->x;
        p->lastY = p->y;

        p->x += p->vx;
        p->y += p->vy;


        //
        // Bounce projectiles off of boundaries
        //
        if (p->x < 0) {
            p->x = 0;
            p->vx *= -1 * FRICTION;
        }
        if (p->x >= SCREEN_WIDTH) {
            p->x = SCREEN_WIDTH-1;
            p->vx *= -1 * FRICTION;
        }
        if (p->y < 0) {
            p->y = 0;
            p->vy *= -1 * FRICTION;
        }
        if (p->y >= SCREEN_HEIGHT) {
            p->y = SCREEN_HEIGHT-1;
            p->vy *= -1 * FRICTION;
        }


        //
        // Compute new vx and vy
        //
        for (int j=0; j<num_projectiles; j++) {
            if (i == j) continue;

            struct projectile *q = get_projectile(j);

            double rSqrd = pow(q->x - p->x, 2) + pow(q->y - p->y, 2);
            double r = sqrt(rSqrd);

            if (r < 10) {
                continue;
            }

            double theta = atan2(q->y - p->y, q->x - p->x);
            double fx = p->mass / rSqrd * cos(theta);
            double fy = p->mass / rSqrd * sin(theta);

            p->vx += fx;
            p->vy += fy;
        }

    }
}