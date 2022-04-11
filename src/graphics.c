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

#ifndef GRAPHICS_C
#define GRAPHICS_C

#include "graphics.h"
////#include "vector.h"
//#include "config.h"

const char NUMS_SMALL[] = { 0x3f, 0x0c, 0x3f, 0x3f, 0x33, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x33, 0x0c, 0x30, 0x30, 0x33, 0x03, 0x03, 0x30, 0x33, 0x33, 0x33, 0x0c, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x30, 0x3f, 0x3f, 0x33, 0x0c, 0x03, 0x30, 0x30, 0x30, 0x33, 0x30, 0x33, 0x30, 0x3f, 0x0c, 0x3f, 0x3f, 0x30, 0x3f, 0x3f, 0x30, 0x3f, 0x30, 0x00, 0x00 };
const char NUMS_MED[] = { 0xff, 0x3c, 0xff, 0xff, 0xc3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x30, 0xc0, 0xc0, 0xc3, 0x03, 0x03, 0xc0, 0xc3, 0xc3, 0xc3, 0x30, 0xc0, 0xc0, 0xc3, 0x03, 0x03, 0xc0, 0xc3, 0xc3, 0xc3, 0x30, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xc3, 0x30, 0x03, 0xc0, 0xc0, 0xc0, 0xc3, 0xc0, 0xc3, 0xc0, 0xc3, 0x30, 0x03, 0xc0, 0xc0, 0xc0, 0xc3, 0xc0, 0xc3, 0xc0, 0xff, 0x30, 0xff, 0xff, 0xc0, 0xff, 0xff, 0xc0, 0xff, 0xff };
const int NUMS_XL[] = {0x3ffc, 0xc00, 0x3ffc, 0x3ffc, 0x3c00, 0xffff, 0x3ffc, 0xffff, 0x3ffc, 0x3ffc, 0xffff, 0xf00, 0xffff, 0xffff, 0x3c00, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xfc3f, 0xfc0, 0xfc3f, 0xfc3f, 0x3f00, 0x3f, 0xfc3f, 0xfc00, 0xfc3f, 0xfc3f, 0xfc3f, 0xff0, 0xfc3f, 0xfc3f, 0x3f00, 0x3f, 0xfc3f, 0xfc00, 0xfc3f, 0xfc3f, 0xfc3f, 0xfc0, 0xfc3f, 0xfc3f, 0x3fc0, 0x3f, 0xfc3f, 0x3f00, 0xfc3f, 0xfc3f, 0xfc3f, 0xfc0, 0xfc00, 0xfc00, 0x3fc0, 0x3fff, 0x3f, 0x3f00, 0xfc3f, 0xfc3f, 0xfc3f, 0xfc0, 0x3f00, 0xffc0, 0x3ff0, 0xffff, 0x3fff, 0xfc0, 0xffff, 0xfc3f, 0xfc3f, 0xfc0, 0xfc0, 0x3fc0, 0x3ff0, 0xfc00, 0xffff, 0xfc0, 0x3ffc, 0xffff, 0xfc3f, 0xfc0, 0x3f0, 0xfc00, 0x3f3c, 0xfc00, 0xfc3f, 0x3f0, 0xfc3f, 0xfffc, 0xfc3f, 0xfc0, 0xfc, 0xfc00, 0x3f3c, 0xfc3f, 0xfc3f, 0x3f0, 0xfc3f, 0xfc00, 0xfc3f, 0xfc0, 0x3f, 0xfc3f, 0xffff, 0xfc3f, 0xfc3f, 0x3f0, 0xfc3f, 0xfc00, 0xfc3f, 0xfc0, 0xfc3f, 0xfc3f, 0xffff, 0xfc3f, 0xfc3f, 0x3f0, 0xfc3f, 0xfc3f, 0xfc3f, 0xfc0, 0xfc3f, 0xfc3f, 0x3f00, 0xfc3f, 0xfc3f, 0x3f0, 0xfc3f, 0xfc3f, 0xfc3f, 0xfc0, 0xfc3f, 0xfc3f, 0x3f00, 0xfc3f, 0xfc3f, 0x3f0, 0xfc3f, 0xfc3f, 0xffff, 0xfc0, 0xffff, 0xffff, 0x3f00, 0xffff, 0xffff, 0x3f0, 0xffff, 0xffff, 0x3ffc, 0xfc0, 0xffff, 0x3ffc, 0x3f00, 0x3ffc, 0x3ffc, 0x3f0, 0x3ffc, 0x3ffc};

volatile int * const VGA_ADDR = (int *)  0xFFF00000;
volatile int paddle_x_old = 0;
volatile vector2 ball_pos_old;

void draw_num_small(int number, int address) {
	int digit = 0;

	for(int rowOffset = 40; rowOffset >= 0; rowOffset -= 10) {
		int graphic = 0;
		digit = (number >> 12) & 15;
		graphic |= (int)NUMS_SMALL[digit + rowOffset];
		digit = (number >> 8) & 15;
		graphic |= (int)(NUMS_SMALL[digit + rowOffset]) << 8;
		digit = (number >> 4) & 15;
		graphic |= (int)(NUMS_SMALL[digit + rowOffset]) << 16;
		digit = number & 15;
		graphic |= (int)(NUMS_SMALL[digit + rowOffset]) << 24;
		*((int *)(VGA_ADDR + address)) = graphic;
		address -= 64;
	}
}
void draw_num_med(int number, int address, int colormask) {
	int digit = 0;

	for(int rowOffset = 60; rowOffset >= 0; rowOffset -= 10) {
		int graphic = 0;
		digit = (number >> 8) & 15;
		graphic |= (int)NUMS_MED[digit + rowOffset];
		digit = (number >> 4) & 15;
		graphic |= (int)(NUMS_MED[digit + rowOffset]) << 10;
		digit = number & 15;
		graphic |= (int)(NUMS_MED[digit + rowOffset]) << 20;
		graphic &= colormask;
		*((int *)(VGA_ADDR + address)) = graphic;
		address -= 64;
	}
}
void draw_num_xl(int number, int address, int colormask) {
	//int digit = 0;

	for(int rowOffset = 150; rowOffset >= 0; rowOffset -= 10) {
		int graphicr = 0;
		int graphicl = 0;

		graphicr = NUMS_XL[(number & 15) + rowOffset] << 16;
		graphicr |= NUMS_XL[((number >> 4) & 15) + rowOffset] >> 2;
		graphicr &= colormask;

		graphicl = NUMS_XL[((number >> 4) & 15) + rowOffset] << 30;
		graphicl |= NUMS_XL[((number >> 8) & 15) + rowOffset] << 12;
		graphicl &= colormask;

		*((volatile int *)(VGA_ADDR + address)) = graphicl;
		*((volatile int *)(VGA_ADDR + address + 1)) = graphicr;

		address -= 64;
	}
}

void draw_paddle(volatile vector2_b pos) {
	volatile int* address = VGA_ADDR + Y_TO_ADDR(pos.y);
	address += paddle_x_old;
	for (int y = 0; y < PADDLE_HEIGHT; y++) {
		for (int x = 0; x < PADDLE_WIDTH; x++) {
			*(address + x) = 0;
		}
		address += 64;
	}
	address = VGA_ADDR + POS_TO_ADDR(pos);
	//address += pos.x;
	for (int y = 0; y < PADDLE_HEIGHT; y++) {
		for (int x = 0; x < PADDLE_WIDTH; x++) {
			*(address + x) = 0xffffffff;
		}
		address += 64;
	}
	paddle_x_old = pos.x;
}

void draw_ball(volatile vector2 pos) {
	// Clear old position
	int targetxl = BALL_TO_X_MIN(ball_pos_old);
	for (int y = BALL_TO_Y_MIN(ball_pos_old); y <= BALL_TO_Y_MAX(ball_pos_old); y++) {
		*(VGA_ADDR + XYF_ADDR(targetxl, y)) = 0;
	}
	int targetxr = BALL_TO_X_MAX(ball_pos_old); // in case it overlaps 2 blocks
	if (XF_TO_ADDR(targetxl) != XF_TO_ADDR(targetxr)) {
		for (int y = BALL_TO_Y_MIN(ball_pos_old); y <= BALL_TO_Y_MAX(ball_pos_old); y++) {
			*(VGA_ADDR + XYF_ADDR(targetxr, y)) = 0;
		}
	}
	ball_pos_old = pos;
	// Draw the ball
	targetxl = BALL_TO_X_MIN(pos);
	for (int y = BALL_TO_Y_MIN(pos); y <= BALL_TO_Y_MAX(pos); y++) {
		*(VGA_ADDR + XYF_ADDR(targetxl, y)) = 1023 << (XF_TO_SUB_ADDR(BALL_TO_X_MIN(pos)) * 2);
	}
	targetxr = BALL_TO_X_MAX(pos); // in case it overlaps 2 blocks
	if (XF_TO_ADDR(targetxl) != XF_TO_ADDR(targetxr)) {
		for (int y = BALL_TO_Y_MIN(pos); y <= BALL_TO_Y_MAX(pos); y++) {
			*(VGA_ADDR + XYF_ADDR(targetxr, y)) = 1023 >> (10 - (XF_TO_SUB_ADDR(BALL_TO_X_MAX(pos)) * 2));
		}
	}
}


void clear_screen(int color) {
	for (volatile int* i = VGA_ADDR; i < VGA_ADDR + 0x21c00; i++) {
		*i = color;	
	}
}

void draw_walls() {
	volatile int* address = VGA_ADDR + WALL_L_ADDR;
	for (int i = 0; i < 540; i++)
	{
		*address = 0xc0000000;
		address += WALL_R_OFFSET;
		*address = 0x00000003;
		address += (64-WALL_R_OFFSET);
	}
	
}

void draw_bricks(char brickarr[BRICKS_HEIGHT][BRICKS_WIDTH]) {
	volatile int* address = VGA_ADDR + WALL_L_ADDR + 1;
	for (int y = 0; y < BRICKS_HEIGHT; y++)
	{
		for (int yp = 0; yp < BRICK_H_PX; yp++)
		{
			if (yp == 0 || yp == BRICK_H_PX-1) {
				address += 64;
			} else {
				for (int x = 0; x < BRICKS_WIDTH; x++) {
					switch (brickarr[y][x])
					{
						case 3:
							*address = 0xfffffffc;
							address++;
							*address = 0x3fffffff;
							break;
						case 2:
							*address = 0xfffffffc & HGRAY;
							address++;
							*address = 0x3fffffff & HGRAY;
							break;
						case 1:
							*address = 0xfffffffc & LGRAY;
							address++;
							*address = 0x3fffffff & LGRAY;
							break;
						default:
							*address = 0;
							address++;
							*address = 0;
							break;
					}
					address++;
				}
				address += 64-(BRICKS_WIDTH*2);
			}
		}
	}
}


#endif