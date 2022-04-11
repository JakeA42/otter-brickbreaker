/////////////////////////////////
//
// Brick breaker for RV32 Otter
// CPE 233, W21
// 3/10/2021
// By: Jake Alt
//
// Description: graphics functions
//
/////////////////////////////////

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "vector.h"
#include "config.h"

#define WHITE 0xffffffff
#define HGRAY 0xaaaaaaaa
#define LGRAY 0x55555555
#define BLACK 0


void draw_bricks(char brickarr[BRICKS_HEIGHT][BRICKS_WIDTH]);

void draw_num_small(int number, int address);

void draw_num_med(int number, int address, int colormask);

void draw_num_xl(int number, int address, int colormask);

void draw_ball(volatile vector2 pos);

void draw_paddle(volatile vector2_b pos);

void clear_screen(int color);

void draw_walls();


#endif