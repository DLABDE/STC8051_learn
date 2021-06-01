#include<reg52.h>
sbit led=P2^0;
sbit open=P2^1;
sbit close=P2^2;
void delay(void)   //13us   Îó²î -1.064236111111us
{
    unsigned char a;
    for(a=4;a>0;a--);
}
void delay50ms(void)   //Îó²î -0.000000000011us
{
    unsigned char a,b,c;
    for(c=3;c>0;c--)
        for(b=44;b>0;b--)
            for(a=173;a>0;a--);
}

void main()
{
	int a;
	led=0;
	open=1;
	close=1;
	while(open==0)
	{
		delay50ms();
		if(open==0)
		{
			while(!open);
			for(a=10;a>=0;a--)
			{
			 	led=1;
				delay();
				led=0;
				delay();
			}
		}
		open=1;
	}
	while(close==0)
	{
		delay50ms();
		if(close==0)
		{
			while(!close);
			for(a=20;a>=0;a--)
			{
			 	led=1;
				delay();
				led=0;
				delay();
			}
		}
		close=1; 
	}
}