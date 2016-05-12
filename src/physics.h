#ifndef PHYSICS_H
#define PHYSICS_H

#define FRICTION 0.60
#define GRAV_CONST 0.05

struct projectile {
    double x, y, vx, vy;
    double lastX, lastY;
    double mass;
    int diam;
};

struct projectile* get_projectile(int i);
int get_num_projectiles();

void add_projectile(double x, double y, double vx, double vy, double mass);

void physics_tick();
#endif
