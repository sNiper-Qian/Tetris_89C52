#ifndef  _BLOCK_H
#define  _BLOCK_H
#define uchar unsigned char
#define uint unsigned int

enum shape
{
	square=0,leftz,rightz,tri,stripe,leftl,rightl
};
typedef struct cube
{
	uchar locx;
	uchar locy;
}Cube_Type;

typedef struct block
{
	uchar shape;
	uchar stop;
	uchar direction;
	Cube_Type s[4];
}Block_Type;

uchar generate(struct block *x,uchar shape_now);

void rotate(struct block *x);

void drop(struct block *x);

void drop_doublespeed(struct block *x);

void left_move(struct block *x);

void right_move(struct block *x);

uchar max4(uchar a,uchar b,uchar c,uchar d);

uchar verify_border(uchar x,uchar y);

uchar eliminate(struct block *x);

uchar game_over();

uchar get_map(uchar x,uchar y);

void update_map(uchar x,uchar y,uchar color);

void initialize_map();

void drop_row(uchar ub,uchar row);

void draw_level(uchar level);

#endif

