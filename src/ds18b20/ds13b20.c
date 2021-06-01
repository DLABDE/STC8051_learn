//����ds13b20
#include<reg52.h>
#include<intrins.h>

#define uchar unsigned char
#define uint unsigned int

sbit DSPORT=P3^2;	 //����

sbit ge=P3^3;	 //����λ	�ߵ�ƽ����
sbit shi=P3^4;	 //�ڶ�λ
sbit bai=P3^5;	 //��һλ

sbit ledg=P3^6;	   //��ֵ	�ߵ�ƽ����
sbit ledr=P3^7;	   //��ֵ

sbit a=P2^0;
sbit b=P2^1;
sbit c=P2^2;
sbit d=P2^3;
sbit e=P2^4;
sbit f=P2^5;
sbit g=P2^6;
sbit dp=P2^7;

void open()		 //�忨��ʼ��
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
uchar Ds18b20Init()			   //��ʼ��
{
	uchar i=0;
	DSPORT=0;
	i=70;				   //��ʱ480us-960us
	while(i--);
	DSPORT=1; 
	i=0;
	while(DSPORT)
	{
		Delay1ms(1);		//�ȴ�60-210us����
		i++;
		if(i>5)
		{
			return 0;		   //��ʼ��ʧ��	  ��ʱ
		}
	 	
	}
	return 1;
}
void DsWriteByte(uchar dat)
{
	uchar i,j;
	for(j=0;j<8;j++)
	{
		DSPORT=0;					//����
		DSPORT=dat&0x01;			//ȡ���λ1
		i=6;						//��ʱ60-120us
		while(i--);
		DSPORT=1; 					//�ͷ�
		dat>>=1;
	}
}
uchar DsReadByte()
{
	uint i,j;
	uchar bi,byte;  
	for(j=8;j>0;j--)
	{
		DSPORT=0; 				 //����1us
		i++;
		DSPORT=1;				   //�ͷ�
		i++;
		i++;
		bi=DSPORT;					 //15us�ڶ�ȡ
		byte=(byte>>1)|(bi<<7);		 //��λ
		i=4;
		while(i--);
	}
	return byte;
}
	 	
void DSchangetemp()
{
	Ds18b20Init();
	Delay1ms(1);
	DsWriteByte(0XCC);		   //����ROMָ��
	DsWriteByte(0x44);		   //�¶�װ��ָ��
}

void DSreadtempcom()
{
	Ds18b20Init();
	Delay1ms(1);
	DsWriteByte(0XCC);
	DsWriteByte(0xbe);			//���ݴ���ָ��
}

int DSreadtemp()
{
	int temp=0;
	uchar tmh,tml;
	DSchangetemp();
	DSreadtempcom();
	tml=DsReadByte();		 //��ȡ���ֽ�
	tmh=DsReadByte(); 		 //��ȡ���ֽ�
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
		if(temp>0)		   		//�������
		{
			ledg=0;
			ledr=1;
		}
		else						 //С�����
		{
			ledg=1;
			ledr=0;
		}
		if(temp<0)					 //С�����
		{
			temp=temp-1;			   //ת��
	   		temp=~temp;
	   		tp=temp;
	   		temp=tp*0.0625*100+0.5;	   //��׼�¶�
		}	 
		else
		{
	 		tp=temp;
	 		temp=tp*0.0625*100+0.5;
		}
		
		one=temp/10000;				  //��λ
		two=temp%10000/1000;		  //ʮλ
		three=temp%10000%1000/100;	  //��λ
		threeb=temp%100/10;			  //С����һλ
		
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