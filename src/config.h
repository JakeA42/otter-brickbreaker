/////////////////////////////////
//
// Brick breaker for RV32 Otter
// CPE 233, W21
// 3/10/2021
// By: Jake Alt
//
// Description: configuration values
//
/////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H

#define PADDLE_TOPADDR 33280
#define PADDLE_Y 520
#define PADDLE_HEIGHT 5
#define PADDLE_WIDTH 3
#define PADDLE_WIDTH_N 61
#define PADDLE_MIN 4
#define PADDLE_MAX 39

#define WALL_L_ADDR 3
#define WALL_R_OFFSET 39
#define WALL_L_X 63
#define WALL_R_X 672


#define BRICKS_WIDTH 19
#define BRICKS_HEIGHT 18
#define BRICK_H_PX 16

#define FLOOR_Y 539
#define POS_DIV 5

#endif