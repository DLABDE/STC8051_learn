#include<reg52.h>
#include<intrins.h>

#define unchar unsigned char

#define READ_MINUTE   0x83	 //分
#define WRITE_MINUTE  0x82

#define READ_HOUR     0x85	  //时
#define WRITE_HOUR    0x84

#define WRITE_SECOND  0x80	  //秒
#define READ_SECOND   0x81

#define WRITE_PROTECT 0x8E	  //保护

#define READ_DATE     0x87	  //号
#define WRITE_DATE    0x86

#define READ_MONTH    0x89	   //月
#define WRITE_MONTH   0x88

#define READ_DAY      0x8B	   //星期
#define WRITE_DAY     0x8A

#define READ_YEAR     0x8D	   //年
#define WRITE_YEAR    0x8C

sbit ACC_7=ACC^7;			//累加器

sbit SCLK=P3^7;                 
sbit DIO=P3^6;                    
sbit CE=P3^5;

sbit beed=P3^4;                     
sbit sled=P2^0;
sbit wei=P2^2;
sbit duan=P2^3;
sbit week=P2^1;

sbit one=P2^4;
sbit two=P2^5;
sbit three=P2^6;
sbit four=P2^7;
/*
sbit p0=P1^0;
sbit p1=P1^1;
sbit p2=P1^2;
sbit p3=P1^3;
sbit p4=P1^4;
sbit p5=P1^5;
sbit p6=P1^6;
sbit p7=P1^7;
*/
int sleep(int a)
{
	int x,y;
	for(x=a;x>0;x--)
		for(y=114;y>0;y--);
	return 0;
}

unchar TOTEN(unchar dat)
{
    unchar dat1;				   //BCD8421转十进制
    dat1=dat/16;                          
    dat=dat%16;                        
    dat=dat+dat1*10;
    return(dat);
}
unchar TOBDC(unchar dat)		//十进制转BCD8421
{
	unchar m,n;
	m=dat/10;
	n=dat%10;
	dat=m*16+n;
	return(dat);
}

void Write1302(unchar addr,dat)     
{
	unchar i,temp;
    CE=0;
	_nop_();                     
    SCLK=0;
	_nop_();                   
    CE=1;
	_nop_();                     
    for(i=8;i>0;i--) 
	{     
		SCLK=0;
		_nop_();
        temp=addr;
        DIO=(bit)(temp&0x01);
		_nop_();       
        addr>>=1;               
        SCLK=1;
		_nop_();
	}
	for(i=8;i>0;i--) 
	{     
		SCLK=0;
		_nop_();
        temp=dat;
        DIO=(bit)(temp&0x01);
		_nop_();          
        dat>>=1;                   
        SCLK=1;
		_nop_();
	}
	CE=0;
	_nop_();         
}

unchar Read1302(unchar addr)
{
	unchar i,temp;
    CE=0;
	_nop_();           
    SCLK=0;
	_nop_();             
    CE=1;
	_nop_();  
	for(i=8;i>0;i--)                   
	{     
		SCLK=0;
		_nop_();
        temp=addr;
        DIO=(bit)(temp&0x01);
		_nop_();         
        addr>>=1;                             
        SCLK=1;
		_nop_();
	}
	for(i=8;i>0;i--) 
	{
		SCLK=1;
		_nop_();
        ACC_7=DIO;
        SCLK=0;
		_nop_();
        ACC>>=1;
	}     
	CE=0;
	_nop_();
	return(ACC);
}

void Initial()    		//ds1302初始化
{ 
	Write1302(WRITE_PROTECT,0X00);     
    Write1302(WRITE_SECOND,0x56);          
    Write1302(WRITE_MINUTE,0x34);     
    Write1302(WRITE_HOUR,0x12);        
    Write1302(WRITE_PROTECT,0x80);                
}

int openwei(int a)		//wei选择位选 
{
	if(a==0){wei=1;P1=0xf0;week=0;}
	if(a==1){wei=1;P1=0x70;week=0;}
	if(a==2){wei=1;P1=0xb0;wei=0;week=0;}
	if(a==3){wei=1;P1=0xd0;wei=0;week=0;}
	if(a==4){wei=1;P1=0xe0;wei=0;week=0;}
	if(a==5){wei=1;P1=0xf8;wei=0;week=0;}		
	if(a==6){wei=1;P1=0xf4;wei=0;week=0;}		
	if(a==7){wei=1;P1=0xf2;wei=0;week=0;}		
	if(a==8){wei=1;P1=0xf1;wei=0;week=0;}		
	if(a==9){wei=1;P1=0xf0;wei=0;week=1;}
	return 0;
}	

int openduan(int d,a)		//duan选择位 a显示数
{
	if(d==1||d==2||d==3||d==4)
	{
		if(a==0){duan=1;_nop_();P1=0x7e;_nop_();duan=0;}
		if(a==1){duan=1;P1=0x12;duan=0;}
		if(a==2){duan=1;P1=0xbc;duan=0;}
		if(a==3){duan=1;P1=0xb6;duan=0;}
		if(a==4){duan=1;P1=0xd2;duan=0;}
		if(a==5){duan=1;P1=0xe6;duan=0;}
		if(a==6){duan=1;P1=0xee;duan=0;}
		if(a==7){duan=1;P1=0x32;duan=0;}
		if(a==8){duan=1;P1=0xfe;duan=0;}
		if(a==9){duan=1;P1=0xf6;duan=0;}
		if(a==10){duan=1;P1=0x01;duan=0;}
		if(a==11){duan=1;P1=0x00;duan=0;}								
	}
	else if(d==6||d==7||d==8||d==9)
	{
		if(a==0){duan=1;P1=0x83;duan=0;}
		if(a==1){duan=1;P1=0xed;duan=0;}
		if(a==2){duan=1;P1=0x43;duan=0;}
		if(a==3){duan=1;P1=0xc9;duan=0;}
		if(a==4){duan=1;P1=0x2d;duan=0;}
		if(a==5){duan=1;P1=0x19;duan=0;}
		if(a==6){duan=1;P1=0x11;duan=0;}
		if(a==7){duan=1;P1=0xcd;duan=0;}
		if(a==8){duan=1;P1=0x81;duan=0;}
		if(a==9){duan=1;P1=0x09;duan=0;}
		if(a==10){duan=1;P1=0xfe;duan=0;}
		if(a==11){duan=1;P1=0xff;duan=0;}
	}
	else if(d==5)
	{
		if(a==0){duan=1;P1=0x81;duan=0;}
		if(a==1){duan=1;P1=0xed;duan=0;}
		if(a==2){duan=1;P1=0xc2;duan=0;}
		if(a==3){duan=1;P1=0xc8;duan=0;}
		if(a==4){duan=1;P1=0xac;duan=0;}
		if(a==5){duan=1;P1=0x98;duan=0;}
		if(a==6){duan=1;P1=0x90;duan=0;}
		if(a==7){duan=1;P1=0xcd;duan=0;}
		if(a==8){duan=1;P1=0x80;duan=0;}
		if(a==9){duan=1;P1=0x88;duan=0;}
		if(a==10){duan=1;P1=0x7f;duan=0;}
		if(a==11){duan=1;P1=0xff;duan=0;}
	}
	return 0;
}

void start()				//板卡初始化
{
	sled=0;
	beed=0;

	CE=0;
	DIO=0;
	SCLK=1;

	openwei(0);
	one=1;
	two=1;
	three=1;
	four=1;
	
	sled=1;
	beed=1;		
}

void main()
{
	//int aa;
	//int bc;
	start();
	Initial();	 		 
	beed=0;
	openwei(0);
	sleep(50);
	openduan(2,1);
	sleep(1000);
	beed=1;
	sleep(500);

	//while(1);
	
	
	
	/*for(aa=1;aa<10;aa++)
	{
		openwei(aa,0);
		for(bc=0;bc<11;bc++)
		{
			openduan(aa,bc);
			beed=1;
			sleep(500);
			openduan(aa,11);
			beed=0;
			sleep(20);

		}
		openwei(aa,1);	
	}		*/
}