#include<reg52.h>
#include<stdio.h>
#include<math.h>
//����
int x=50;//Ѫ��Ũ��0~100����ʼ��50(0������    0~25����     >=75:��)
int k=0;//����ʳ��,  ��ʼ��0
int w=0;//θ��ʳ��,  ��ʼ��0
int zt;	  //���������ȵ�AB״̬
int xt; //Ѫ��
int gt;//�����ĸ���ԭ

//ָʾ (�ߵ�ƽ����)
sbit led1=P1^0;			//Ѫ��ָʾ��
sbit led2=P1^1;			//1:����2:��3:��
sbit led3=P1^2;

sbit eat=P1^3;			//��ʳ	eat:ָʾ��  eat_s:����
sbit eat_s=P3^2;      	//����P3^2(10k���ʹ���)		   �ж�IT0

sbit wei=P1^4;			 //θ

sbit xues=P1^5;			 //Ѫ��Ѫ�Ǳ仯 xues:���� xuej:�½�
sbit xuej=P1^6;

sbit xqn=P1^7;			 //������

sbit yda=P3^0;			 //�ȵ�ϸ��AB
sbit ydb=P3^1;

sbit dead=P2^0;			  //�����ֹͣ
sbit gt_s=P2^1;			   //����ԭ����


//aneat  �жϺ��� P3^2  IT0
void aneat(int a)			//1��    0�ر�
{
	if(a==1)
	{
		EA=1;	 //���ж� ��
		EX0=1;	 //�ⲿ�ж� ��
		IT0=1;	 //INT0��P3^2���½��ش���
	}
	else if(a==0)
	{
		EA=0;
	}
}

//�忨��ʼ��
void play()
{
	P1=02;	   //�˽��Ƴ�ʼ��P1		(10000000)B
	eat_s=1;	   
	dead=0;
	yda=0;
	ydb=0;
}

//��ʱ N ms  (11.0592MHz)
void delay_ms(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
		for(j=0;j<125;j++)
		{
			;
		}
}

//���������жϺ���		  
int xue()
{
		if(xt==0)					   //����
		{
			aneat(0);
			P1=00;
			eat_s=1;
			dead=1;
			yda=0;
			ydb=0;
			while(1);	
		}
		else if((xt>25)&&(xt<75))			//Ѫ������			(����0��
		{
			led2=0;
			led3=0;
			led1=1;
			return 0;
		}
		else if(xt>=75)   				//Ѫ�Ǹ�					 ������10��
		{
			led1=0;
			led3=0;
			led2=1;
			return 10;
		}
		else if((xt>0)&&(xt<=25))   	//Ѫ�ǵ�					  ������1��
		{
			led1=0;
			led2=0;
			led3=1;
			return 1;
		}		
}


//������
void main()
{
	play();		   //�忨��ʼ��
	aneat(1);		//���ж�

	gt=20;		//��ʼ������ԭ����
	xt=x;		 //��ʼ��Ѫ��Ũ��
	zt=0;		   //��ʼ�� �ȵ��������� ״̬

	xue();			//������������

	while(1)				   //��ѭ������ֹ�ܷ�
	{
		if(gt>0)				//��ʾ����ԭ
		{
			gt_s=1;
		}

		delay_ms(200);		  //Ѫ��ͬ������
		xuej=1;
		delay_ms(300);
		xuej=0;
		xt-=1;
		xue();
					 
		while(k>0)						 //����ʳ��ת�Ƶ�θ��	  ��k-->w��
		{
			delay_ms(150);
			wei=1;
			delay_ms(150);
			wei=0;
			k-=1;
			w+=1;
			xue();
		}
									 				 
		while(w>0)		  //��������		  (w-->xt)
		{
			delay_ms(200);
			xues=1;
			wei=0;
			delay_ms(200);
			xues=0;
			wei=1;
			w-=1;
			xt+=1;
			xue();
			if(w==0)
			{
				wei=0;
			}
		}


		zt=xue();						   //�ռ��������������������ȵ�AB
		if(zt==10)							//Ѫ�ǽ̸ߣ������� �̼� �ȵ�Bϸ�� �� Ѫ�� �½�������ֵ
		{
			delay_ms(600);
			while(xt>=50)
			{
				xqn=1;					  
				ydb=1;						

				xuej=1;						  //Ѫ���½� ,����ԭ���
				delay_ms(100);
				xt-=1;						   
				gt+=1;
				xuej=0;
				delay_ms(100);
				xue();

				if(gt>0)				
				{
					gt_s=1;
				}
			}
			xqn=0;
			ydb=0;
		}

		if((zt==1)&&(gt>0))						//Ѫ�ǽϵͣ� ������ �̼� �ȵ�Aϸ�� �� Ѫ�� ����������ֵ
		{
			delay_ms(600);
			while(gt>0)
			{
				xqn=1;					  
				yda=1;						

				xues=1;						  //Ѫ������ ,����ԭ����
				delay_ms(100);
				xt+=1;						   
				gt-=1;
				xues=0;
				delay_ms(100);
				xue();
				if(xt==50)
				{
					xqn=0;
					yda=0;
					break;
				}	
			}
			xqn=0;
			yda=0;
			if(gt==0)
			{
				gt_s=0;
			}		
		}



	}		
}


//�жϴ���
void zhongduan() interrupt 0
{
	if(eat_s==0)					//ιʳ
		{
		delay_ms(25);
		if(eat_s==0)
			{
			xuej=0;
			xues=0;
			wei=0;
			while((k>=0)&&(k<=100))
				{
					if(eat_s==0)
					{
						delay_ms(100);
						eat=1;
						delay_ms(100);
						eat=0;
						k+=1;
						xue();
					}
						if(eat_s==1)
						{
							break;
						}
				}		
			} 
		}					
}