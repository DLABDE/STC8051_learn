#include<reg52.h>

sbit sdi=P1^0;
sbit lck=P1^4;
sbit sck=P2^3;
sbit ks_out=P2^7;
unsigned char ks_b;


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
	ks_out=1;
	hc595(0x00);
	ks_b=0;
	while(1)
	{
if(ks_out==0)	//判断是否上升沿跳变， 有则又信号触发
	 {
	  yanshi(10);		//延时，再次判断是否有触发信号
	  if(ks_out==0)
	  {
	      
		  while(!ks_out);	//等待触发信号结束
		  yanshi(30);
		  ks_b=!ks_b;  //按位取反  则micb 只可能是两个值 0x00 0xff   //   micb=！micb； 逻辑 0 或 1
		  if(ks_b==0)
			  {
			  hc595(0x0a);//继电器闭合
			  yanshi(500);
			  }
		  if(ks_b==1)
		  	  {
			  hc595(0x02);//继电器断开
			  yanshi(500);
		      }
	  }
	 }
	 }
}