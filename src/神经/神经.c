#include<reg52.h>

sbit a=P2^0;	   //���� ͷ		   
sbit b=P2^1;	   //���� β
sbit aj=P2^2;		//����			   �͵�ƽ����

sbit led=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;						  //�͵�ƽ����
sbit led3=P1^3;
sbit led4=P1^4;
sbit led5=P1^5;
sbit led6=P1^6;
sbit led7=P1^7;

int x=0;
				 
void delay(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
		for(j=0;j<125;j++)
		{
			;
		}
}

void main()
{
	aj=1;
	while(1)			//	   ѭ��
	{
		if(aj==0)
		{
			delay(25);
			if(aj==0)
			{
				a=0;
				delay(1000);
				a=1;
				delay(800);

				led=0;			//		����͵�ƽ
				delay(700);
				led=1;

				led1=0;
	 			delay(700);
				led1=1;


				led2=0;
				delay(700);
				led2=1;


				led3=0;
	    		delay(700);
				led3=1;


				led4=0;
	    		delay(700);
				led4=1;

				led5=0;
	    		delay(700);
				led5=1;


				led6=0;
	    		delay(700);
				led6=1;

				led7=0;
				delay(700);
				led7=1;

				delay(500);
				b=0;
				delay(1000);
				b=1;
				aj=1;
			}
		}
	}
}