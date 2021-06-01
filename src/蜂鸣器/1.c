#include<reg52.h>
sbit sdi=P1^0;
sbit lck=P1^4;
sbit sck=P2^3;

void yanshi(int i)
{
	int x,y;
   for(x=i;x>0;x--)
   	for(y=114;y>0;y--);
}

void hc595(int m)
{
	int a;
	sck=0;
	for(a=0;a<8;a++)
	{
	 	lck=0;
		sdi=(m<<a)&0x80;
		lck=1;
	}
	sck=1;
	sdi=1;	
}

void main()
{
	int d;
	for(d=1000;d>=0;)
	{
	hc595(0x04);
	yanshi(d);
	hc595(0x00);
	yanshi(d);
	d=d-15;
	}
}	