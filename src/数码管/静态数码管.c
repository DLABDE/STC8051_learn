/* ************************************************************************************
																					  *
C mask工作室出品   QQ群：512023245													  *
作者：杜																			  *
																					  *
																			 		  *
																					  *
说明：																				  *
 本程序适用于51单片机	 【单片机：STC 89C52RC    开发板：Easy Board 51				  *
                                                          版本：XK-0 V5.0】			  *
 本程序将实现8个数码管以一次1S依次显示  0 1 2 3 4 5 6 7 8 9 1.    					  *
 ***************************************************************************************/

#include<reg52.h>	   //调用

sbit dual=P2^5;	  //申明
sbit wela=P2^6;
sbit p8=P0^7;  //（下面有几个没写出来 ）
sbit p1=P0^0;
sbit p2=P0^1;
sbit p3=P0^2;
sbit p6=P0^5;
sbit p4=P0^3;
sbit p7=P0^6;
sbit p5=P0^4;

int a,b,c=500;		  //0.5s
int d=500;			  //0.5s

void yanshi()	 //延时  0.5s
{
	 for(a=c;a>0;a--)
   	{
   	 for(b=114;b>0;b--);
	}
}

void xiaoying()			//强制消影  用时0.5s
{
	    for(a=d;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		dual=1;
		wela=1;
		p1=1;
		p2=1;
		p3=1;
		p4=1;
		p5=1;
		p6=1;
		p7=1;
		dual=0;
		P0=0xff;
		wela=0;
}


void main()		//主函数
{
		//00000000000000000000
		dual=1;
		wela=1;
		p1=0;
		p2=0;
		p3=0;
		p4=0;
		p5=0;
		p6=0;
		//p7=1;				 [高电平可以审略，因为51单片机默认为高电平]
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();






		//1111111111111111111
		dual=1;
		wela=1;
		//p1=1;
		//p2=1;
	//	p3=1;
	//	p4=1;
		p5=0;
		p6=0;
	//	p7=1;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();		//调用消影函数
		yanshi();	   //调用延时函数




		  //222222222222222222
		dual=1;
		wela=1;
		p1=0;
		p2=0;
	//	p3=1;
		p4=0;
		p5=0;
	//	p6=1;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
        yanshi();



	   //33333333333333333333333333
		dual=1;
		wela=1;
		p1=0;
		p2=0;
		p3=0;
		p4=0;
	//	p5=1;
	//	p6=1;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
        yanshi();





	   //44444444444444444444444
		dual=1;
		wela=1;
	//	p1=1;
		p2=0;
		p3=0;
	//	p4=1;
	//	p5=1;
		p6=0;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
    	yanshi();
		




			//555555555555555555
		dual=1;
		wela=1;
		p1=0;
	//	p2=1;
		p3=0;
		p4=0;
	//	p5=1;
		p6=0;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();
		
		



		//6666666666666
		dual=1;
		wela=1;
		p1=0;
	//	p2=1;
		p3=0;
		p4=0;
		p5=0;
		p6=0;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();
		
		



		//777777777777
		dual=1;
		wela=1;
		p1=0;
		p2=0;
		p3=0;
		//p4=1;
		//p5=1;
	//	p6=1;
	//	p7=1;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();
		
		
		//888888888888888888888
		dual=1;
		wela=1;
		p1=0;
		p2=0;
		p3=0;
		p4=0;
		p5=0;
		p6=0;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();

		//999999999999999
		dual=1;
		wela=1;
		p1=0;
		p2=0;
		p3=0;
		p4=0;
	//	p5=1;
		p6=0;
		p7=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();
		
		
		
		
		//1.   1.   1.  1.
		dual=1;
		wela=1;
	//	p1=1;
	//	p2=1;
	//	p3=1;
		p4=1;
		p5=0;
		p6=0;
	//	p7=1;
		p8=0;
		dual=0;
		P0=0xff;
		wela=0;
		xiaoying();
		yanshi();				 
} 
