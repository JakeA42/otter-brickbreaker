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

#include "physics.h"
//#include "vector.h"
//#include "config.h"

void check_wall_collision(volatile vector2* ballpos, volatile vector2* velocity, int lwall_x, int rwall_x) {
	if (ballpos->x >= rwall_x - 3 && velocity->x > 0) {
		velocity->x = -velocity->x;
	} else if (ballpos->x <= lwall_x + 3 && velocity->x < 0) {
		velocity->x = -velocity->x;
	}
	if (ballpos->y <= 2 && velocity->y < 0)
	{
		velocity->y = -velocity->y;
	}
}
int check_floor_collision(volatile vector2* ballpos, int floor_y) {
	return (ballpos->y >= floor_y);
}

void check_paddle_collision(volatile vector2* ballpos, volatile vector2* velocity, int paddle_x) {
	if (ballpos->y >= PADDLE_Y - 1 && ballpos->y <= PADDLE_Y + PADDLE_HEIGHT / 2) {
		if (XF_TO_ADDR(ballpos->x) >= paddle_x && XF_TO_ADDR(ballpos->x) < paddle_x + PADDLE_WIDTH && velocity->y > 0) {
			velocity->y = -velocity->y;
			velocity->x += (XF_TO_ADDR(ballpos->x) - paddle_x) - (PADDLE_WIDTH / 2);
			if (velocity->x > 3) velocity->x = 3;
			else if (velocity->x < -3) velocity->x = -3;
		}
	}
}
int check_brick_collision(volatile vector2* ballpos, volatile vector2* velocity, char bricks[BRICKS_HEIGHT][BRICKS_WIDTH]) {
	// UP
	int targety = (BALL_TO_Y_MIN_P(ballpos) - 1) / BRICK_H_PX;
	int targetx = (XF_TO_ADDR(ballpos->x) - 4) / 2;
	if (velocity->y < 0 && targety >= 0 && targety < BRICKS_HEIGHT && targetx >= 0 && targetx < BRICKS_WIDTH && bricks[targety][targetx] != 0)
	{
		bricks[targety][targetx]--;
		velocity->y = -velocity->y;
		return 2;
	}
	// DOWN
	targety = (BALL_TO_Y_MAX_P(ballpos) + 1) / BRICK_H_PX;
	if (velocity->y > 0 && targety < BRICKS_HEIGHT && targetx >= 0 && targetx < BRICKS_WIDTH && bricks[targety][targetx] != 0)
	{
		bricks[targety][targetx]--;
		velocity->y = -velocity->y;
		return 2;
	}
	// LEFT
	targety = (ballpos->y) / BRICK_H_PX;
	targetx = (XF_TO_ADDR(ballpos->x) - 5) / 2;

	if (velocity->x < 0 && XF_TO_SUB_ADDR(ballpos->x) == 2 && targety < BRICKS_HEIGHT && targetx >= 0 && targetx < BRICKS_WIDTH && bricks[targety][targetx] != 0)
	{
		bricks[targety][targetx]--;
		velocity->x = -velocity->x;
		return 2;
	}
	// RIGHT
	targetx = (XF_TO_ADDR(ballpos->x) - 3) / 2;
	if (velocity->x > 0 && XF_TO_SUB_ADDR(ballpos->x) == 14 && targety < BRICKS_HEIGHT && targetx >= 0 && targetx < BRICKS_WIDTH && bricks[targety][targetx] != 0)
	{
		bricks[targety][targetx]--;
		velocity->x = -velocity->x;
		return 2;
	}
	return 0;
}

int update_ball(volatile vector2* pos, volatile vector2* velocity, int paddle_x, char bricks[BRICKS_HEIGHT][BRICKS_WIDTH]) {
	check_paddle_collision(pos, velocity, paddle_x);
	check_wall_collision(pos, velocity, WALL_L_X, WALL_R_X);
	int score = check_brick_collision(pos, velocity, bricks);
	pos->x_fine += velocity->x;
	pos->x = pos->x_fine >> POS_DIV;
	pos->y_fine += velocity->y;
	pos->y = pos->y_fine >> POS_DIV;
	
	return score;
}
