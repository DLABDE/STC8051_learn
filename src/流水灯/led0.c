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
 本程序将实现 8个LED灯流水依次循环显示 (未精简)   					  *
 ***************************************************************************************/
#include<reg52.h>

sbit led=P1^0;	  //   申明
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;
sbit led4=P1^4;
sbit led5=P1^5;
sbit led6=P1^6;
sbit led7=P1^7;

void main()		   //	主函数
{
	int M=500;		  // 定义整形变量
	unsigned char a,b;	 //	   定义无符号字符变量
	while(1)			//	   循环
	{
		led=0;			//		输入低电平

	    for(a=M;a>0;a--)		  //延时
   		{
   			for(b=114;b>0;b--);
		}

		led=1;				   //	输入高电平


		led1=0;
	    for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led1=1;


		led2=0;
	    for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led2=1;


		led3=0;
	    for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led3=1;


		led4=0;
	    for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led4=1;


		led5=0;
	    for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led5=1;


		led6=0;
	    for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led6=1;

		led7=0;
		for(a=M;a>0;a--)
   		{
   			for(b=114;b>0;b--);
		}
		led7=1;
	}	
}