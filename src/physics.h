/////////////////////////////////
//
// Brick breaker for RV32 Otter
// CPE 233, W21
// 3/10/2021
// By: Jake Alt
//
// Description: collisions and movement
//
/////////////////////////////////

#ifndef PHYSICS_H
#define PHYSICS_H

#include "vector.h"
#include "config.h"

void check_wall_collision(volatile vector2* ballpos, volatile vector2* velocity, int lwall_x, int rwall_x);
int check_floor_collision(volatile vector2* ballpos, int floor_y);
void check_paddle_collision(volatile vector2* ballpos, volatile vector2* velocity, int paddle_x);
int check_brick_collision(volatile vector2* ballpos, volatile vector2* velocity, char bricks[BRICKS_HEIGHT][BRICKS_WIDTH]);

int update_ball(volatile vector2* pos, volatile vector2* velocity, int paddle_x, char bricks[BRICKS_HEIGHT][BRICKS_WIDTH]);

#endif