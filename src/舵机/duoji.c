#include"eboard.h"
#define uchar unsigned char
#define uint unsigned int

sbit pwm=P2^2;      //ÐÅºÅÊä³ö
sbit pp=P2^3;
sbit mq=P1^5;
uchar count=0;
uchar n=22;  
uchar m=22;


void domove(uchar i,uchar j)
{
		TMOD = 0x01;				 //  0.1ms   11.0592Mhz
		TH0 = 0xFF;
    TL0 = 0XA4;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
		m=i;
		n=j;
		delay(3);
}
void main()
{
		uint a;
		init_1602();
		mq=1;
		domove(17,21);
    while(1)
    {
			a=1.1*getdistance();
			write_1602(0x85,0);
			write_1602(0x30+a/10000%10,1);
			write_1602(0x30+a/1000%10,1);
			write_1602(0x30+a/100%10,1);
			write_1602(0x30+a/10%10,1);
			if(a<=13630)
			{
				domove(7,12);
				mq=0;
				delay(2400);
				mq=1;
				domove(17,21);
				a=14000;
			}
			delay(300);
    }
}

void Timer() interrupt 1     
{
    TH0 = 0xFF;
    TL0 = 0xA4;
	count++;
    if(count<=200)
    {
    	if(count<=n)
        {
        	pwm=1;
        }
        else
        {
         	pwm=0;
        }
		if(count<=m)
        {
			pp=1;
        }
        else
        {
			pp=0;
        }
    }
    else
    {
    	count=0;
     	pwm=0;
		pp=0;
    }
}