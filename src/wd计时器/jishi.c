#include<reg52.h>

sbit led=P1^0;
sbit sw=P1^2;

int a=18000;

int time(int M)
{
	int a,b;
	for(a=M;a>0;a--)		
   		{
   			for(b=114;b>0;b--);
		}
}
void main()
{	  
	while(1)
	{
		if (a>0)
		{
			sw=1;
			led=1;
			time(500);
			led=0;
			time(500);
			a=a-1;
		}	 
		sw=0;
	}		
}
