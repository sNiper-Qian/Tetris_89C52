#include <reg52.h>
#include <intrins.h>
#include <driver.h>
#include <stdlib.h>
#include <pic.h>
#include <block.h>

uchar xdata map[16][16]={0};

void initialize_map()
{
	uchar i,j;
	for(i=0;i<16;i++)
	for(j=0;j<16;j++)
	map[i][j]=0;
}

uchar get_map(uchar x,uchar y)
{
	return map[x][y];
}

void update_map(uchar x,uchar y,uchar color)
{
	map[x][y]=color;
}


uchar generate(struct block *x,uchar shape_now)
{
	uchar i,j;
	uchar shape_future;
	
	shape_future=TL0;
	shape_future%=5;
	//shape_future=5;
	
	for(i=17;i<=19;i++)
	for(j=7;j<=10;j++)
	draw_cube(i,j,0);
	
	switch(shape_future)
	{
		case square:
			draw_cube(17,7,1);
			draw_cube(18,7,1);
			draw_cube(17,8,1);
			draw_cube(18,8,1);
		break;
		
		case leftz:
			draw_cube(17,7,1);
			draw_cube(18,7,1);
			draw_cube(18,8,1);
			draw_cube(19,8,1);
		break;
		
		case rightz:
			draw_cube(17,8,1);
			draw_cube(18,7,1);
			draw_cube(18,8,1);
			draw_cube(19,7,1);
		break;
		
		case tri:
			draw_cube(17,8,1);
			draw_cube(18,7,1);
			draw_cube(18,8,1);
			draw_cube(19,8,1);
		break;
		
		case stripe:
			draw_cube(18,7,1);
			draw_cube(18,8,1);
			draw_cube(18,9,1);
			draw_cube(18,10,1);
		break;
		
		default: break;
	}

	x->shape=shape_now;
	
	switch(x->shape)
	{
		case square:
			(x->s[0]).locx=7;
			(x->s[0]).locy=0;
			(x->s[1]).locx=8;
			(x->s[1]).locy=0;
			(x->s[2]).locx=7;
			(x->s[2]).locy=1;
			(x->s[3]).locx=8;
			(x->s[3]).locy=1;
		break;
		
		case leftz:
			(x->s[0]).locx=7;
			(x->s[0]).locy=0;
			(x->s[1]).locx=8;
			(x->s[1]).locy=0;
			(x->s[2]).locx=8;
			(x->s[2]).locy=1;
			(x->s[3]).locx=9;
			(x->s[3]).locy=1;
		break;
		
		case rightz:
			(x->s[0]).locx=7;
			(x->s[0]).locy=1;
			(x->s[1]).locx=8;
			(x->s[1]).locy=0;
			(x->s[2]).locx=8;
			(x->s[2]).locy=1;
			(x->s[3]).locx=9;
			(x->s[3]).locy=0;
		break;
		
		case tri:
			(x->s[0]).locx=7;
			(x->s[0]).locy=1;
			(x->s[1]).locx=8;
			(x->s[1]).locy=0;
			(x->s[2]).locx=8;
			(x->s[2]).locy=1;
			(x->s[3]).locx=9;
			(x->s[3]).locy=1;
		break;
		
		case stripe:
			(x->s[0]).locx=6;
			(x->s[0]).locy=0;
			(x->s[1]).locx=7;
			(x->s[1]).locy=0;
			(x->s[2]).locx=8;
			(x->s[2]).locy=0;
			(x->s[3]).locx=9;
			(x->s[3]).locy=0;
		break;
		
		case leftl:
			(x->s[0]).locx=7;
			(x->s[0]).locy=1;
			(x->s[1]).locx=8;
			(x->s[1]).locy=1;
			(x->s[2]).locx=9;
			(x->s[2]).locy=1;
			(x->s[3]).locx=9;
			(x->s[3]).locy=0;
		break;
		
		default: break;
	}
	for(i=0;i<4;i++)
	draw_cube((x->s[i]).locx,(x->s[i]).locy,1);
	x->direction=0;
	x->stop=0;
	return shape_future;
}



void rotate(struct block *x)
{
	switch(x->shape)
	{
		case leftz:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[2].locx-1,x->s[2].locy)==1||get_map(x->s[2].locx-1,x->s[2].locy+1)==1||x->s[2].locx-1<0||x->s[2].locy+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx-1,x->s[2].locy,1);
					draw_cube(x->s[2].locx-1,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locy++;
					x->s[3].locx-=2;
					x->s[3].locy++;
					x->direction++;
					x->direction%=2;
				break;
					
				case 1:
					if(get_map(x->s[0].locx,x->s[0].locy-1)==1||get_map(x->s[0].locx+2,x->s[0].locy)==1||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy-1,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locy--;
					x->s[3].locx+=2;
					x->s[3].locy--;
					x->direction++;
					x->direction%=2;
				break;
			}
		break;
			
		case rightz:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[2].locx+1,x->s[2].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy+1)==1||x->s[2].locy+1>15||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locx+=2;
					x->s[0].locy++;
					x->s[3].locy++;
					x->direction++;
					x->direction%=2;
				break;
					
				case 1:
					if(get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[2].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[2].locx-1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locy--;
					x->s[0].locx-=2;
					x->s[3].locy--;
					x->direction++;
					x->direction%=2;
				break;
			}
		break;
			
		case tri:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[2].locx,x->s[2].locy+1)==1||x->s[2].locy+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					
					//update location
					x->s[0].locx++;
					x->s[0].locy++;
					x->direction++;
					x->direction%=4;
				break;
					
				case 1:
					if(get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[2].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx-1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					
					//update location
					x->s[1].locy++;
					x->s[1].locx--;
					x->direction++;
					x->direction%=4;
				break;
					
				case 2:
					if(get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[2].locy-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx,x->s[2].locy-1,1);
				
					//clear dots
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[3].locy--;
					x->s[3].locx--;
					x->direction++;
					x->direction%=4;
				break;
					
				case 3:
					if(get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					
					//update location
					x->s[0].locy--;
					x->s[0].locx--;
					x->s[1].locy--;
					x->s[1].locx++;
					x->s[3].locy++;
					x->s[3].locx++;
					x->direction++;
					x->direction%=4;
				break;
			}
		break;
			
		case stripe:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[1].locx,x->s[1].locy-1)==1||get_map(x->s[1].locx,x->s[1].locy+1)==1
						||get_map(x->s[1].locx,x->s[1].locy+2)==1||x->s[1].locy-1<0||x->s[1].locy+2>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx,x->s[1].locy+2,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
					draw_cube(x->s[1].locx,x->s[1].locy-1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locx++;
					x->s[0].locy--;
					x->s[2].locx-=1;
					x->s[2].locy+=1;
					x->s[3].locx-=2;
					x->s[3].locy+=2;
					x->direction++;
					x->direction%=2;
				break;
					
				case 1:
					if(get_map(x->s[1].locx-1,x->s[1].locy-1)==1||get_map(x->s[1].locx+2,x->s[1].locy)==1
						||get_map(x->s[1].locx+1,x->s[1].locy)==1||x->s[1].locx+2>15||x->s[1].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx-1,x->s[1].locy,1);
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[1].locx+2,x->s[1].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locx--;
					x->s[0].locy++;
					x->s[2].locx+=1;
					x->s[2].locy-=1;
					x->s[3].locx+=2;
					x->s[3].locy-=2;
					x->direction++;
					x->direction%=2;
				break;
			}
		break;
			
		case leftl:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[1].locx,x->s[1].locy-2)==1||get_map(x->s[1].locx,x->s[1].locy-1)==1||x->s[1].locy-2<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx,x->s[1].locy-1,1);
					draw_cube(x->s[1].locx,x->s[1].locy-2,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locx++;
					x->s[0].locy--;
					x->s[3].locx--;
					x->s[3].locy--;
					x->direction++;
					x->direction%=4;
				break;
					
				case 1:
					if(get_map(x->s[1].locx-1,x->s[1].locy+1)==1||get_map(x->s[1].locx-1,x->s[1].locy)==1||x->s[2].locy+1>15||x->s[1].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx-1,x->s[1].locy+1,1);
					draw_cube(x->s[1].locx-1,x->s[1].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locy+=2;
					x->s[0].locx--;
					x->s[3].locy+=2;
					x->s[3].locx--;
					x->direction++;
					x->direction%=4;
				break;
					
				case 2:
					if(get_map(x->s[2].locx,x->s[2].locy+2)==1||get_map(x->s[2].locx,x->s[2].locy+1)==1||x->s[2].locy+2>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+2,1);
				
					//clear dots
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					
					//update location
					x->s[3].locy++;
					x->s[3].locx+=2;
					x->s[0].locy++;
					x->s[0].locx+=2;
					x->direction++;
					x->direction%=4;
				break;
					
				case 3:
					if(get_map(x->s[2].locx,x->s[2].locy-1)==1||get_map(x->s[2].locx-2,x->s[2].locy)==1||x->s[2].locx-2<0||x->s[2].locy-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx,x->s[2].locy-1,1);
					draw_cube(x->s[2].locx-2,x->s[2].locy,1);
	
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					x->s[0].locy-=2;
					x->s[0].locx-=2;
					x->s[3].locy-=2;
					x->direction++;
					x->direction%=4;
				break;
			}
		break;	
			
		default: break;
	}
}



void drop(struct block *x)
{	
	uchar i;
	ES = 0;     
	ET0 = 0;
  //RI = 0;  

	switch(x->shape)
	{
		//square
		case square:
					//verify
					if(get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||x->s[2].locy+1>15||x->s[3].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);
//						for(i=0;i<16;i++)
//					for(j=0;j<16;j++)
//						draw_dot(i+65,j,map[i+1][j+1]);
						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
		case leftz:
			switch(x->direction)
			{
				case 0:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||
						get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||x->s[2].locy+1>15||x->s[3].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 1:
					//verify
					if(get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||x->s[2].locy+1>15||x->s[3].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
			}
		break;
			
		case rightz:
			switch(x->direction)
			{
				case 0:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||
						get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||x->s[2].locy+1>15||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 1:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||x->s[2].locy+1>15||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
			}
		break;
			
		case tri:
			switch(x->direction)
			{
				case 0:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||
						get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||x->s[2].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 1:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[0]).locx+1,(x->s[0]).locy)==1||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 2:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||
						get_map((x->s[1]).locx,(x->s[1]).locy+1)==1||x->s[1].locy+1>15||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 3:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[0]).locx-1,(x->s[0]).locy)==1||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
			}
		break;
			
		case stripe:
			switch(x->direction)
			{
				case 0:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[1]).locx,(x->s[1]).locy+1)==1||get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||
						get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||x->s[3].locy+1>15)
					{
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[1].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 1:
					//verify
					if(get_map((x->s[3]).locx,(x->s[3]).locy+1)==1||x->s[3].locy+1>15)
					{
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
			}
		break;
			
		case leftl:
			switch(x->direction)
			{
				case 0:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[1]).locx,(x->s[1]).locy+1)==1||
						get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||x->s[2].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 1:
					//verify
					if(get_map((x->s[1]).locx,(x->s[1]).locy+1)==1||get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||x->s[1].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
				
					//clear dots
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 2:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[1]).locx,(x->s[1]).locy+1)==1||
						get_map((x->s[2]).locx,(x->s[2]).locy+1)==1||x->s[1].locy+1>15||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[2].locx,x->s[2].locy+1,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
					
				case 3:
					//verify
					if(get_map((x->s[0]).locx,(x->s[0]).locy+1)==1||get_map((x->s[1]).locx,(x->s[1]).locy+1)==1||x->s[0].locy+1>15)
					{
						//delay(100);
						update_map((x->s[0]).locx,(x->s[0]).locy,1);
						update_map((x->s[1]).locx,(x->s[1]).locy,1);
						update_map((x->s[2]).locx,(x->s[2]).locy,1);
						update_map((x->s[3]).locx,(x->s[3]).locy,1);
						//delay(100);

						x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx,x->s[0].locy+1,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locy++;
					}
				break;
			}
		break;
							
		default: break;
		
	}
	 ES = 1;            
   //RI = 1; 
	 ET0 = 1;
}

void right_move(struct block *x)
{
	uchar i;
	switch(x->shape)
	{
		//square
		case square:
					if(get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[3].locx+1,x->s[3].locy)==1||x->s[1].locx+1>15||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
				
		case leftz:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[3].locx+1,x->s[3].locy)==1||x->s[1].locx+1>15||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 1:
					if(get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[3].locx+1,x->s[3].locy)==1||
						get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[1].locx+1>15||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
			}
			break;
						
		case rightz:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[2].locx+1>15||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 1:
					if(get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[3].locx+1,x->s[3].locy)==1||
						get_map(x->s[0].locx+1,x->s[0].locy)==1||x->s[3].locx+1>15||x->s[0].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
			}
		break;
			
		case tri:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[3].locx,x->s[3].locy-1)==1||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
					draw_cube(x->s[3].locx,x->s[3].locy-1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 1:
					if(get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[3].locx+1,x->s[3].locy)==1||
						get_map(x->s[0].locx+1,x->s[0].locy)==1||x->s[3].locx+1>15||x->s[0].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 2:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[3].locx,x->s[3].locy+1)==1||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
					draw_cube(x->s[3].locx,x->s[3].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
				
				case 3:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||
						get_map(x->s[0].locx+1,x->s[0].locy)==1||x->s[3].locx+1>15||x->s[0].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
			}
		break;
		
		case stripe:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 1:
					if(get_map(x->s[0].locx+1,x->s[0].locy)==1||get_map(x->s[1].locx+1,x->s[1].locy)==1||get_map(x->s[3].locx+1,x->s[3].locy)==1||
						get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[1].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[1].locx+1,x->s[1].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
			}
			break;	
			
		case leftl:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[3].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 1:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[0].locx+1,x->s[0].locy)==1||
						get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[3].locx+1>15||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 2:
					if(get_map(x->s[0].locx+1,x->s[0].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
				
				case 3:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||
						get_map(x->s[0].locx+1,x->s[0].locy)==1||x->s[3].locx+1>15||x->s[0].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
			}
		break;	
			
		default: break;
	}
}

void left_move(struct block *x)
{
	uchar flag=0,i;
	switch(x->shape)
	{
		//square
		case square:
					if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[0].locx-1<0||x->s[2].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
					draw_cube(x->s[2].locx-1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
					
			case leftz:
				switch(x->direction)
				{
					case 0:
						if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[0].locx-1<0||x->s[2].locx-1<0)
						{
							//x->stop=1;
							return;
						}
						//generate dots
						draw_cube(x->s[0].locx-1,x->s[0].locy,1);
						draw_cube(x->s[2].locx-1,x->s[2].locy,1);
					
						//clear dots
						draw_cube(x->s[1].locx,x->s[1].locy,0);
						draw_cube(x->s[3].locx,x->s[3].locy,0);
						
						//update location
						for(i=0;i<4;i++)
						{
							x->s[i].locx--;
						}
					break;
						
					case 1:
						if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[1].locx-1,x->s[1].locy)==1||
							get_map(x->s[3].locx-1,x->s[3].locy)==1||x->s[0].locx-1<0||x->s[3].locx-1<0)
						{
							//x->stop=1;
							return;
						}
						//generate dots
						draw_cube(x->s[0].locx-1,x->s[0].locy,1);
						draw_cube(x->s[1].locx-1,x->s[1].locy,1);
						draw_cube(x->s[3].locx-1,x->s[3].locy,1);
					
						//clear dots
						draw_cube(x->s[1].locx,x->s[1].locy,0);
						draw_cube(x->s[2].locx,x->s[2].locy,0);
						draw_cube(x->s[3].locx,x->s[3].locy,0);
						
						//update location
						for(i=0;i<4;i++)
						{
							x->s[i].locx--;
						}
					break;
				}
				break;
				
			case rightz:
				switch(x->direction)
				{
					case 0:
						if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[1].locx-1,x->s[1].locy)==1||x->s[0].locx-1<0||x->s[1].locx-1<0)
						{
							//x->stop=1;
							return;
						}
						//generate dots
						draw_cube(x->s[0].locx-1,x->s[0].locy,1);
						draw_cube(x->s[1].locx-1,x->s[1].locy,1);
					
						//clear dots
						draw_cube(x->s[2].locx,x->s[2].locy,0);
						draw_cube(x->s[3].locx,x->s[3].locy,0);
						
						//update location
						for(i=0;i<4;i++)
						{
							x->s[i].locx--;
						}
					break;
						
					case 1:
						if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[1].locx-1,x->s[1].locy)==1||
							get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[1].locx-1<0||x->s[2].locx-1<0)
						{
							//x->stop=1;
							return;
						}
						//generate dots
						draw_cube(x->s[0].locx-1,x->s[0].locy,1);
						draw_cube(x->s[1].locx-1,x->s[1].locy,1);
						draw_cube(x->s[2].locx-1,x->s[2].locy,1);
					
						//clear dots
						draw_cube(x->s[1].locx,x->s[1].locy,0);
						draw_cube(x->s[0].locx,x->s[0].locy,0);
						draw_cube(x->s[3].locx,x->s[3].locy,0);
						
						//update location
						for(i=0;i<4;i++)
						{
							x->s[i].locx--;
						}
					break;
				}
		break;
				
		case tri:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[0].locx,x->s[0].locy-1)==1||x->s[0].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
					draw_cube(x->s[0].locx,x->s[0].locy-1,1);
				
					//clear dots
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
					
				case 3:
					if(get_map(x->s[1].locx-1,x->s[1].locy)==1||get_map(x->s[3].locx-1,x->s[3].locy)==1||
						get_map(x->s[0].locx-1,x->s[0].locy)==1||x->s[1].locx-1<0||x->s[0].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
					draw_cube(x->s[1].locx-1,x->s[1].locy,1);
					draw_cube(x->s[3].locx-1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
					
				case 2:
					if(get_map(x->s[1].locx-1,x->s[1].locy)==1||get_map(x->s[1].locx,x->s[1].locy+1)==1||x->s[1].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[1].locx-1,x->s[1].locy,1);
					draw_cube(x->s[1].locx,x->s[1].locy+1,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
				
				case 1:
					if(get_map(x->s[2].locx-1,x->s[2].locy)==1||get_map(x->s[1].locx-1,x->s[1].locy)==1||
						get_map(x->s[0].locx-1,x->s[0].locy)==1||x->s[1].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
					draw_cube(x->s[2].locx-1,x->s[2].locy,1);
					draw_cube(x->s[1].locx-1,x->s[1].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
			}
		break;
			
		case stripe:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[0].locx-1,x->s[0].locy)==1||x->s[0].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
				
					//clear dots
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
					
				case 1:
					if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[1].locx-1,x->s[1].locy)==1||get_map(x->s[3].locx-1,x->s[3].locy)==1||
						get_map(x->s[2].locx-1,x->s[2].locy)==1||x->s[1].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
					draw_cube(x->s[2].locx-1,x->s[2].locy,1);
					draw_cube(x->s[1].locx-1,x->s[1].locy,1);
					draw_cube(x->s[3].locx-1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
			}
			break;	
		
		case leftl:
			switch(x->direction)
			{
				case 0:
					if(get_map(x->s[0].locx-1,x->s[0].locy)==1||get_map(x->s[3].locx-1,x->s[3].locy)==1||x->s[0].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[3].locx-1,x->s[3].locy,1);
					draw_cube(x->s[0].locx-1,x->s[0].locy,1);
				
					//clear dots
					draw_cube(x->s[2].locx,x->s[2].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx--;
					}
				break;
					
				case 1:
					if(get_map(x->s[3].locx-1,x->s[3].locy)==1||get_map(x->s[0].locx-1,x->s[0].locy)==1||
						get_map(x->s[1].locx-1,x->s[1].locy)==1||x->s[3].locx-1<0)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
					
				case 2:
					if(get_map(x->s[0].locx+1,x->s[0].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||x->s[2].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
				
				case 3:
					if(get_map(x->s[3].locx+1,x->s[3].locy)==1||get_map(x->s[2].locx+1,x->s[2].locy)==1||
						get_map(x->s[0].locx+1,x->s[0].locy)==1||x->s[3].locx+1>15||x->s[0].locx+1>15)
					{
						//x->stop=1;
						return;
					}
					//generate dots
					draw_cube(x->s[0].locx+1,x->s[0].locy,1);
					draw_cube(x->s[2].locx+1,x->s[2].locy,1);
					draw_cube(x->s[3].locx+1,x->s[3].locy,1);
				
					//clear dots
					draw_cube(x->s[0].locx,x->s[0].locy,0);
					draw_cube(x->s[1].locx,x->s[1].locy,0);
					draw_cube(x->s[3].locx,x->s[3].locy,0);
					
					//update location
					for(i=0;i<4;i++)
					{
						x->s[i].locx++;
					}
				break;
			}
		break;	
			
		default: break;
	}
}

uchar eliminate(struct block *x)
{
	uchar i,j,k,flag,top,upper_bound,num=0;
	if(x->s[0].locy<=x->s[1].locy) top=x->s[0].locy;
	else top=x->s[1].locy;
	if(x->s[2].locy<=top) top=x->s[2].locy;
	if(x->s[3].locy<=top) top=x->s[3].locy;
	
	for(i=15;i>=top;i--)
	{
		flag=0;
		for(j=0;j<16;j++)
		{
			if(map[j][i]==0) flag=1;
		}
		if(flag==0)
		{
			
			upper_bound=i;
			num++;
			for(k=0;k<16;k++)
			{
				draw_cube(k,i,0);
				update_map(k,i,0);
			}
		}
	}
	if(num>0)
	{
		drop_row(upper_bound,num);
	}
	return num;
}

void drop_row(uchar ub,uchar num)
{
	uchar i,j;
	for(i=ub-1;i>=1;i--)
	{
		for(j=0;j<16;j++)
		{
			draw_cube(j,i+num,map[j][i]);
			update_map(j,i+num,map[j][i]);
			update_map(j,i,0);
		}
	}
}

uchar game_over()
{
	uchar i,j;
	for(i=0;i<16;i++)
	{
		if(map[i][2]!=0)
		{
			write_cmd(0x30);
			for(j=0;j<3;j++)
			{
				write_cmd(0x08);
				delay(1000);
				write_cmd(0x0C);
				delay(1000);
			}
			return 1;
		}
	}
	delay(1);
	return 0;
}

void drop_doublespeed(struct block *x)
{
	for(;;)
	{
	drop(x);
	ES=0;
	if(x->stop==1) return;
	}
}