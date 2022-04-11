/////////////////////////////////
//
// Brick breaker for RV32 Otter
// CPE 233, W21
// 3/10/2021
// By: Jake Alt
//
// Description: vector structures
//
/////////////////////////////////

#ifndef VECTOR_H
#define VECTOR_H

#define XF_TO_SUB_ADDR(x) ((x) & 15)
#define XF_TO_ADDR(x) ((x) >> 4)
#define Y_TO_ADDR(y) ((y) << 6)
#define POS_TO_ADDR(pos) (pos.x + (pos.y << 6))
#define FINE_TO_BLOCK(pos) ((pos.x >> 4) + (pos.y << 6))
#define POS_TO_ADDR_P(pos) (pos->x + (pos->y << 6))
#define FINE_TO_BLOCK_P(pos) ((pos->x >> 4) + (pos->y << 6))

#define XYF_ADDR(x, y) (((x) >> 4) + ((y) << 6))
#define XY_ADDR(x, y) ((x) + ((y) << 6))


#define BALL_TO_X_MIN(pos) (pos.x - 2)
#define BALL_TO_X_MAX(pos) (pos.x + 2)
#define BALL_TO_Y_MIN(pos) (pos.y - 2)
#define BALL_TO_Y_MAX(pos) (pos.y + 2)

#define BALL_TO_X_MIN_P(pos) (pos->x - 2)
#define BALL_TO_X_MAX_P(pos) (pos->x + 2)
#define BALL_TO_Y_MIN_P(pos) (pos->y - 2)
#define BALL_TO_Y_MAX_P(pos) (pos->y + 2)


typedef struct 
{
	int x, y;
} vector2_b;

typedef struct 
{
	int x, y;
	int x_fine, y_fine;
} vector2;

#endif