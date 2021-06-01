#include<reg52.h>
#include<stdio.h>
#include<math.h>
//参数
int x=50;//血糖浓度0~100，初始化50(0：死亡    0~25：低     >=75:高)
int k=0;//嘴中食物,  初始化0
int w=0;//胃中食物,  初始化0
int zt;	  //下丘脑与胰岛AB状态
int xt; //血糖
int gt;//储备的肝糖原

//指示 (高电平触发)
sbit led1=P1^0;			//血糖指示灯
sbit led2=P1^1;			//1:正常2:高3:低
sbit led3=P1^2;

sbit eat=P1^3;			//进食	eat:指示灯  eat_s:按键
sbit eat_s=P3^2;      	//按键P3^2(10k拉低触发)		   中断IT0

sbit wei=P1^4;			 //胃

sbit xues=P1^5;			 //血浆血糖变化 xues:上升 xuej:下降
sbit xuej=P1^6;

sbit xqn=P1^7;			 //下丘脑

sbit yda=P3^0;			 //胰岛细胞AB
sbit ydb=P3^1;

sbit dead=P2^0;			  //生命活动停止
sbit gt_s=P2^1;			   //肝糖原有无


//aneat  中断函数 P3^2  IT0
void aneat(int a)			//1打开    0关闭
{
	if(a==1)
	{
		EA=1;	 //总中断 打开
		EX0=1;	 //外部中断 打开
		IT0=1;	 //INT0（P3^2）下降沿触发
	}
	else if(a==0)
	{
		EA=0;
	}
}

//板卡初始化
void play()
{
	P1=02;	   //八进制初始化P1		(10000000)B
	eat_s=1;	   
	dead=0;
	yda=0;
	ydb=0;
}

//延时 N ms  (11.0592MHz)
void delay_ms(unsigned int i)
{
	unsigned int j;
	for(;i>0;i--)
		for(j=0;j<125;j++)
		{
			;
		}
}

//生命体征判断函数		  
int xue()
{
		if(xt==0)					   //死亡
		{
			aneat(0);
			P1=00;
			eat_s=1;
			dead=1;
			yda=0;
			ydb=0;
			while(1);	
		}
		else if((xt>25)&&(xt<75))			//血糖正常			(返回0）
		{
			led2=0;
			led3=0;
			led1=1;
			return 0;
		}
		else if(xt>=75)   				//血糖高					 （返回10）
		{
			led1=0;
			led3=0;
			led2=1;
			return 10;
		}
		else if((xt>0)&&(xt<=25))   	//血糖低					  （返回1）
		{
			led1=0;
			led2=0;
			led3=1;
			return 1;
		}		
}


//主函数
void main()
{
	play();		   //板卡初始化
	aneat(1);		//打开中断

	gt=20;		//初始化肝糖原储备
	xt=x;		 //初始化血浆浓度
	zt=0;		   //初始化 胰岛，下丘脑 状态

	xue();			//更新生命体征

	while(1)				   //死循环，防止跑飞
	{
		if(gt>0)				//显示肝糖原
		{
			gt_s=1;
		}

		delay_ms(200);		  //血糖同步降低
		xuej=1;
		delay_ms(300);
		xuej=0;
		xt-=1;
		xue();
					 
		while(k>0)						 //口中食物转移到胃中	  （k-->w）
		{
			delay_ms(150);
			wei=1;
			delay_ms(150);
			wei=0;
			k-=1;
			w+=1;
			xue();
		}
									 				 
		while(w>0)		  //消化吸收		  (w-->xt)
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


		zt=xue();						   //收集生命体征给下丘脑与胰岛AB
		if(zt==10)							//血糖教高，下丘脑 刺激 胰岛B细胞 ， 血糖 下降到正常值
		{
			delay_ms(600);
			while(xt>=50)
			{
				xqn=1;					  
				ydb=1;						

				xuej=1;						  //血糖下降 ,肝糖原变多
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

		if((zt==1)&&(gt>0))						//血糖较低， 下丘脑 刺激 胰岛A细胞 ， 血糖 上升到正常值
		{
			delay_ms(600);
			while(gt>0)
			{
				xqn=1;					  
				yda=1;						

				xues=1;						  //血糖上升 ,肝糖原变少
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


//中断触发
void zhongduan() interrupt 0
{
	if(eat_s==0)					//喂食
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