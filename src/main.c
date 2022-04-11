/////////////////////////////////
//
// Brick breaker for RV32 Otter
// CPE 233, W21
// 3/10/2021
// By: Jake Alt
//
// Description: main
//
/////////////////////////////////

#include "vector.h"
#include "config.h"
#include "graphics.h"
#include "physics.h"
#include <string.h>

const char bricksinit[BRICKS_HEIGHT][BRICKS_WIDTH] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2, 0, 2, 2, 2},
	{1, 0, 3, 3, 0, 0, 3, 3, 3, 0, 3, 3, 3, 0, 0, 3, 3, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 1, 3, 3, 1, 0, 3, 3, 3, 1, 3, 3, 3, 0, 1, 3, 3, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 0, 0},
	{0, 0, 2, 2, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 2, 2, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{2, 2, 2, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 2, 2, 2},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 0, 0, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 0, 0, 2, 0, 0, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1, 3, 3, 2, 0, 0, 2, 2, 2, 0, 2, 2, 2, 3, 3, 2, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

char bricksstate[18][19];

volatile int * const SWITCHES = (int *) 0x11000000;
volatile int * const ENC = (int *) 0x11040000;
volatile int * const LEDS = (int *) 0x11080000;
volatile int * const VBLANK_ADDR = (int *)  0xFFFFFFFF;

volatile int * const SSEG = (int *)  0x110C0000;

volatile vector2_b paddle_pos;
volatile vector2 ball_pos;
volatile vector2 ball_velocity;

volatile int enc_count = 0;
volatile int enc_step = 0;
volatile int enc_dir = 0;
volatile int enc_btn = 0;
volatile int colorval = 0xaaaaaaaa;

volatile int game_active = 0;
volatile int score = 0;
volatile int lives = 0;

#define ENABLE_INT   asm(" li t0, 1		\n\
		      	   la t1, enc_ISR 	\n\
	 	      	   csrw mtvec, t1 	\n\
		      	   csrw mie, t0		");

void update_paddle() {
	if (game_active) paddle_pos.x += enc_count;
	enc_count = 0;
	if (paddle_pos.x > PADDLE_MAX)
	{
		paddle_pos.x = PADDLE_MAX;
	} else if (paddle_pos.x < PADDLE_MIN)
	{
		paddle_pos.x = PADDLE_MIN;
	}
}

void __attribute__((__interrupt__)) enc_ISR()
{
	int reading = *ENC;
	int newval = (reading & 3) ^ 3;
	switch (newval)
	{
		case 0b00:
			if (enc_step == 0b01 && enc_dir == 0) {
				enc_count--;
			} else if (enc_step == 0b10 && enc_dir == 1) {
				enc_count++;
			}
			break;
		case 0b01:
			if (enc_step == 0b00) { // Only set dir when moving from 0b00
				enc_dir = 1; // Moving backwards
			}
			break;
		case 0b10:
			if (enc_step == 0b00) { // Only set dir when moving from 0b00
				enc_dir = 0; // Moving forwards
			}
			break;
	}
	enc_step = newval;
	if (reading & 4) enc_btn = 1;
	colorval = (reading & 8) ? 0xffffffff : 0xaaaaaaaa;
	//asm("li a1, 1 \n    csrw mie, a1 ");
	//asm("mret");
}

void init_round() {
	game_active = 0;
	enc_btn = 0;

	paddle_pos.x = 20;
	paddle_pos.y = PADDLE_Y;
	ball_pos.x = 21*16;
	ball_pos.x_fine = (21*16) << POS_DIV;
	ball_pos.y = PADDLE_Y - 6;
	ball_pos.y_fine = (PADDLE_Y - 6) << POS_DIV;
	ball_velocity.x = 2;
	ball_velocity.y = -2;
}

void initialize() {
	clear_screen(BLACK);
	memcpy(bricksstate, bricksinit, 18*19);
	draw_walls();
	score = 0;
	lives = 3;
	init_round();
}

void update_graphics() {
	
	draw_ball(ball_pos);
	//draw_num_med(bcd, XY_ADDR(50, 150), colorval);
	int bcd = (score % 10) | (((score / 10) % 10) << 4) | (((score / 100) % 10) << 8);

	draw_num_xl(bcd, XY_ADDR(50, 200), colorval);
	draw_num_xl(lives, XY_ADDR(50, 400), colorval);
	draw_paddle(paddle_pos);
}

void main(){

	ENABLE_INT
	initialize();
	draw_bricks(bricksstate);
	while (!enc_btn);
	game_active = 1;
	enc_btn = 0;

	while(1) {

		while (lives)
		{
			if (check_floor_collision(&ball_pos, FLOOR_Y)) {
				lives -= 1;
				init_round();
				update_graphics();
				while (!enc_btn);
				game_active = 1;
				enc_btn = 0;
			}

			update_paddle();
			int dscore = update_ball(&ball_pos, &ball_velocity, paddle_pos.x, bricksstate);
			if (dscore) draw_bricks(bricksstate);
			score += dscore;

			update_graphics();
			for (int i = 0; i < 1000; i++)
			{
				asm("nop");
			}
		}
	}
}

