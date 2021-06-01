#include<reg52.h>

sbit up=P1^0;
sbit up_led=P1^1;
sbit down=P1^2;
sbit down_led=P1^3;
sbit up_sm=P1^4;
sbit down_sm=P1^5;

sbit up_aj=P2^0;
sbit down_aj=P2^1;

void ys(int b)
{
	int i,x,y;
	i=b;
	for(x=i;x>0;x--)
		for(y=114;y>0;y--);	
}

void main()
{
	
	up_sm=1;
	down_sm=1;
	up=1;
	up_led=0;
	down=1;
	down_led=0;
	up_aj=1;
	down_aj=1;

	while(1)
	{
		if(up_aj==0)
		{
			ys(50);
			if(up_aj==0)
			{	
				while(!up_aj);
				down=1;
				down_sm=1;
				down_led=0;

				ys(10);
				up_sm=0;
				ys(10);
				up=0;
				up_led=1;

				up_aj=1;
			}
		}
		
		if(down_aj==0)
		{
			ys(50);
			if(down_aj==0)
			{	
				while(!down_aj);
				up=1;
				up_sm=1;
				up_led=0;

				ys(10);
				down_sm=0;
				ys(10);
				down=0;
				down_led=1;

				down_aj=1;
			}
		}		
	}
}