/* ************************************************************************************
																					  *
C mask�����ҳ�Ʒ   QQȺ��512023245													  *
���ߣ���																			  *
																					  *
																			 		  *
																					  *
˵����																				  *
 ������������51��Ƭ��	 ����Ƭ����STC 89C52RC    �����壺Easy Board 51				  *
                                                          �汾��XK-0 V5.0��			  *
 ������ʵ��8���������һ��1S������ʾ  0 1 2 3 4 5 6 7 8 9 1.    					  *
 ***************************************************************************************/

#include<reg52.h>	   //����

sbit dual=P2^5;	  //����
sbit wela=P2^6;
sbit p8=P0^7;  //�������м���ûд���� ��
sbit p1=P0^0;
sbit p2=P0^1;
sbit p3=P0^2;
sbit p6=P0^5;
sbit p4=P0^3;
sbit p7=P0^6;
sbit p5=P0^4;

int a,b,c=500;		  //0.5s
int d=500;			  //0.5s

void yanshi()	 //��ʱ  0.5s
{
	 for(a=c;a>0;a--)
   	{
   	 for(b=114;b>0;b--);
	}
}

void xiaoying()			//ǿ����Ӱ  ��ʱ0.5s
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


void main()		//������
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
		//p7=1;				 [�ߵ�ƽ�������ԣ���Ϊ51��Ƭ��Ĭ��Ϊ�ߵ�ƽ]
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
		xiaoying();		//������Ӱ����
		yanshi();	   //������ʱ����




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
