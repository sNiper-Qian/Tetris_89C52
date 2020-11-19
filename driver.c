#include <reg52.h>
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
#include <driver.h>
#include <IRController.h>

#define uchar unsigned char
#define uint unsigned int
#define LCD_data P0

void delay(uint x)
{
	int i,j;
	for(i=0;i<x;i++)
	for(j=0;j<50;j++)
	{
		
	}
}

void nop()
{
	uchar i;
	for(i=0;i<20;i++)
	_nop_();
}

void write_cmd(uchar cmd)
{
	RS=0;
	RW=0;
	EN=0;
	P0=cmd;
	EN=1;
	nop();
	EN=0;
}

void write_data(uchar dat)
{
	RS=1;
	RW=0;
	EN=0;
	P0=dat;
	EN=1;
	nop();
	EN=0;
}

uchar read_data()
{
	uchar c;
	EN=0;
	P0=0xFF;
	RS=1;
	RW=1;
	EN=1;
	nop();
	c=P0;
	EN=0;
	return c;
}

void lcd_init()
{
	PSB=1;
	write_cmd(0x30);
	delay(1);
	write_cmd(0x0C);
	delay(1);
	write_cmd(0x01);
	delay(1);
	write_cmd(0x06);
}

void clear_GDRAM(void)
{
  uchar i,j,k;
    
	write_cmd(0x34);        
	i = 0x80;            
	for(j = 0;j < 32;j++)
	{
      write_cmd(i++);
      write_cmd(0x80);
  		for(k = 0;k < 16;k++)
  		{
  		    write_data(0x00);
  		}
	}
	i = 0x80;
 	for(j = 0;j < 32;j++)
	{
 	    write_cmd(i++);
      write_cmd(0x88);	   
  		for(k = 0;k < 16;k++)
  		{
   		    write_data(0x00);
   		} 
	}   
	write_cmd(0x30);       
}

void draw(uchar *pic,uint k)
{
	uchar i,j;
    
	write_cmd(0x34);        
	i = 0x80;       
		
	for(j = 0;j < k;j++)
	{
        write_cmd(i++);
        write_cmd(0x80);
  		  write_data(*pic++);
				write_data(*pic++);
		  	write_data(*pic++);
				write_data(*pic++);
	}

}

void draw_border()
{
	uchar i,j;
    
	write_cmd(0x34);        
	
	i = 0x80;            
	for(j = 0;j < 32;j++)
	{
        write_cmd(i);
        write_cmd(0x84);
  		  write_data(0x80);
				write_cmd(i++);
				write_cmd(0x85);
  		  write_data(0x10);
	}
	write_cmd(0x9F);
	write_cmd(0x85);
	write_data(0x1F);
	write_data(0xFF);
	write_data(0xFF);
	write_data(0xFF);
	write_data(0xFF);
	write_data(0xFF);
	
	i = 0x80;
 	for(j = 0;j < 32;j++)
	{
 	    write_cmd(i);
      write_cmd(0x8C);	   
			write_data(0x80);
			write_cmd(i++);
			write_cmd(0x8D);
  	  write_data(0x10);
	}        
}

void draw_score(uint score)
{
	uchar i=0,bit_1,bit_2,bit_3,bit_4;
	bit_4=score%10;
	score/=10;
	bit_3=score%10;
	score/=10;
	bit_2=score%10;
	score/=10;
	bit_1=score%10;
	
  write_cmd(0x30);
	write_cmd(0x8D);
	write_data(' ');
	write_data(bit_1+48);
	write_data(bit_2+48);
	write_data(bit_3+48);
	write_data(bit_4+48);
}

void draw_level(uchar level)
{
	uchar bit_1,bit_2;
	bit_1=level/10;
	bit_2=level%10;
  write_cmd(0x30);
	write_cmd(0x85);
	write_data(' ');
	write_data('L');
	write_data('v');
	write_data('.');
	write_data(bit_1+48);
	write_data(bit_2+48);
}

void draw_cube(uchar x_type2,uchar y_type2,uchar color)
{
	uchar xlabel,row,x_type1,y_type1,xlabel_bit,temp,i;
	uchar Read_H=0,Read_L=0;
	x_type1=x_type2*4;
	y_type1=y_type2*4;
	write_cmd(0x36);
	
	xlabel=x_type1>>4;            
  xlabel_bit=x_type1 & 0x0F; 
  if(y_type1<32) 
		row=y_type1;
	else     
	{        
		row=y_type1-32;         
		xlabel+=8;      
	} 
		
	write_cmd(row+0x80);
  write_cmd(xlabel+0x80);
	read_data();
	Read_H=read_data();
	Read_L=read_data();

	if(xlabel_bit<8)
	{
		switch(color)
    {
         case 0:
					 if(xlabel_bit<4) temp=0xF<<4;
					 else temp=0xF;
					 Read_H &=(~temp); 
				 break; 
					 
         case 1:
					 if(xlabel_bit<4) temp=0xF<<4;
					 else temp=0xF;
					 Read_H |=temp; 
				 break;
				 
         case 2:
					 if(xlabel_bit<4) temp=0xF<<4;
					 else temp=0xF;
					 Read_H ^=temp; 
				 break;
				 
         default: break;
    } 
	}
	else
	{
			switch(color)
			{
         case 0:
					 if(xlabel_bit<12) temp=0xF<<4;
					 else temp=0xF;
					 Read_L &=(~temp); 
				 break; 
					 
         case 1:
					 if(xlabel_bit<12) temp=0xF<<4;
					 else temp=0xF;
					 Read_L |=temp; 
				 break;
				 
         case 2:
					 if(xlabel_bit<12) temp=0xF<<4;
					 else temp=0xF;
					 Read_L ^=temp; 
				 break;
				 
         default: break;
			} 
	}
	for(i=0;i<4;i++)
	{
		write_cmd(row+0x80+i);
		write_cmd(xlabel+0x80);
		write_data(Read_H);
		write_data(Read_L);
		write_cmd(0x36);
	}
}




