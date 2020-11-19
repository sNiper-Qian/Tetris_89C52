#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>

#define uchar unsigned char
#define uint unsigned int
#define LCD_data P0

sbit RS = P3^5;
sbit RW = P3^6;
sbit EN = P3^4;

sbit PSB = P3^7;
sbit wela = P2^6;
sbit dula = P2^7;

void delay(uint x);

void nop();

void write_cmd(uchar cmd);

void write_data(uchar dat);

uchar read_data(void);

void lcd_init(void);

void clear_GDRAM(void);

void draw(uchar *pic,uint k);

void draw_border();

uchar draw_dot(uchar x,uchar y,uchar color);

void draw_score(uint score);

void draw_cube(uchar x_type2,uchar y_type2,uchar color);




