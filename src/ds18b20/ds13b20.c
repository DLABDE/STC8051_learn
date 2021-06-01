//单个ds13b20
#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit DSPORT=P3^2;	 //总线

sbit ge=P3^3;	 //第三位	高电平触发
sbit shi=P3^4;	 //第二位
sbit bai=P3^5;	 //第一位

sbit ledg=P3^6;	   //负值	高电平触发
sbit ledr=P3^7;	   //正值

sbit a=P2^0;
sbit b=P2^1;
sbit c=P2^2;
sbit d=P2^3;
sbit e=P2^4;
sbit f=P2^5;
sbit g=P2^6;
sbit dp=P2^7;

void open()		 //板卡初始化
{
	DSPORT=1;

	ledg=0;
	ledr=0;

	ge=0;
	shi=0;
	bai=0;

}

void Delay1ms(uint y)			//  1ms=1000us
{
	uint x;
	for(;y>0;y--)
	{
		for(x=110;x>0;x--);	
	}
}
uchar Ds18b20Init()			   //初始化
{
	uchar i=0;
	DSPORT=0;
	i=70;				   //延时480us-960us
	while(i--);
	DSPORT=1; 
	i=0;
	while(DSPORT)
	{
		Delay1ms(1);		//等待60-210us后检测
		i++;
		if(i>5)
		{
			return 0;		   //初始化失败	  超时
		}
	 	
	}
	return 1;
}
void DsWriteByte(uchar dat)
{
	uchar i,j;
	for(j=0;j<8;j++)
	{
		DSPORT=0;					//拉低
		DSPORT=dat&0x01;			//取最低位1
		i=6;						//延时60-120us
		while(i--);
		DSPORT=1; 					//释放
		dat>>=1;
	}
}
uchar DsReadByte()
{
	uint i,j;
	uchar bi,byte;  
	for(j=8;j>0;j--)
	{
		DSPORT=0; 				 //拉低1us
		i++;
		DSPORT=1;				   //释放
		i++;
		i++;
		bi=DSPORT;					 //15us内读取
		byte=(byte>>1)|(bi<<7);		 //移位
		i=4;
		while(i--);
	}
	return byte;
}
	 	
void DSchangetemp()
{
	Ds18b20Init();
	Delay1ms(1);
	DsWriteByte(0XCC);		   //忽略ROM指令
	DsWriteByte(0x44);		   //温度装换指令
}

void DSreadtempcom()
{
	Ds18b20Init();
	Delay1ms(1);
	DsWriteByte(0XCC);
	DsWriteByte(0xbe);			//读暂存器指令
}

int DSreadtemp()
{
	int temp=0;
	uchar tmh,tml;
	DSchangetemp();
	DSreadtempcom();
	tml=DsReadByte();		 //读取低字节
	tmh=DsReadByte(); 		 //读取高字节
	temp=tmh;
	temp<<=8;
	temp|=tml;
	return temp;
}

void Delay(uchar m)
{
	unsigned char ab, bc;
	for(; m > 0; m--)
		for(bc = 142; bc > 0; bc--)
			for(ab = 2; ab > 0; ab--);
}


void duan(int z,p)
{
	switch(z)
	{
		case 0:a=1;b=0;c=0;d=0;e=0;f=0;g=0;dp=1;break;
		case 1:a=1;b=1;c=1;d=0;e=1;f=1;g=0;dp=1;break;
		case 2:a=0;b=1;c=0;d=0;e=0;f=0;g=1;dp=1;break;
		case 3:a=0;b=1;c=0;d=0;e=1;f=0;g=0;dp=1;break;
		case 4:a=0;b=0;c=1;d=0;e=1;f=1;g=0;dp=1;break;
		case 5:a=0;b=0;c=0;d=1;e=1;f=0;g=0;dp=1;break;
		case 6:a=0;b=0;c=0;d=1;e=0;f=0;g=0;dp=1;break;
		case 7:a=1;b=1;c=0;d=0;e=1;f=1;g=0;dp=1;break;
		case 8:a=0;b=0;c=0;d=0;e=0;f=0;g=0;dp=1;break;
		case 9:a=0;b=0;c=0;d=0;e=1;f=0;g=0;dp=1;break;
		case 10:a=1;b=1;c=1;d=1;e=1;f=1;g=1;dp=1;break;
	}
	if(p==0)
	{
	 	dp=0;
	}

}

void wei(int x)
{
	if(x==1)
	{
		shi=0;
		ge=0;
		bai=1;
	}
	else if(x==2)
	{
		bai=0;
		ge=0;
		shi=1;
	}
	else if(x==3)
	{
		bai=0;
		shi=0;
		ge=1;
	}
}

void main()
{
	int temp;
	int one;
	int two;
	int three;
	int threeb;
	int sleep=20;
	float tp;

	open();
	while(1)
	{

		temp=DSreadtemp();
		if(temp>0)		   		//大于零度
		{
			ledg=0;
			ledr=1;
		}
		else						 //小于零度
		{
			ledg=1;
			ledr=0;
		}
		if(temp<0)					 //小于零度
		{
			temp=temp-1;			   //转正
	   		temp=~temp;
	   		tp=temp;
	   		temp=tp*0.0625*100+0.5;	   //标准温度
		}	 
		else
		{
	 		tp=temp;
	 		temp=tp*0.0625*100+0.5;
		}
		
		one=temp/10000;				  //百位
		two=temp%10000/1000;		  //十位
		three=temp%10000%1000/100;	  //个位
		threeb=temp%100/10;			  //小数后一位
		
		if(one!=0)
		{
			wei(1);
			duan(one,1);
			Delay(sleep);
	
			wei(2);
			duan(two,1);
			Delay(sleep-3);
	
			wei(3);
			duan(three,0);
			Delay(sleep-17);
		}
		else if(one==0)
		{
			wei(1);
			duan(two,1);
			Delay(sleep);
	
			wei(2);
			duan(three,0);
			Delay(sleep-3);

			wei(3);
			duan(threeb,1);
			Delay(sleep-17);
		}
	}

}