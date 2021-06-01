#include"eboard.h"
#include<intrins.h>


///////////////////////////////////////////(I2c)(at24c02[0xa0]与pcf8591[0x90])//////////////////////////////
void start_i2c()		 //write_i2c(0xa0,1,0x30+1); read_i2c(0xa0,1); 存入0x31到1中 然后读出	
{						  //读写之间间隔10ms
	sda=1; 
	scl=1;				   //write_i2c(0x09,0x40,255);输出电压数字量0-255(0-5v)   read_i2c(0x90,0x01);读出1通道的数字量
	_nop_();									 
	sda=0;
	scl=0;
	_nop_();		  
}
void end_i2c()
{
    sda=0;        
    scl=1;
    delay_i2c();
    sda=1;
	scl=0;
    delay_i2c();
}
void waitack_i2c()
{
    unsigned char i = 0;
    scl=1;
    delay_i2c();
    while(sda==1&&i<250)i++;
    scl=0;            
    delay_i2c();
}
void writebyte_i2c(unsigned char dat)
{
    unsigned char i;
    for(i=0;i<8;i++)
    {
        scl=0;
       	delay_i2c();
        sda=(dat>>(7-i))&0x01;
		delay_i2c();
        scl=1;
        delay_i2c();
    }
    scl=0;
    sda=1;            
    _nop_();
}
unsigned char readbyte_i2c()
{
    unsigned char dat=0,tmp,i;
    scl=0;
    delay_i2c();
    for(i=0;i<8;i++)
    {
        scl=1;        
        delay_i2c();
        tmp=sda;
        dat=dat<<1;
        dat=dat|tmp;
        delay_i2c();
        scl=0;        
        delay_i2c();
    }
    return dat;
}
void write_i2c(unsigned char s,unsigned char unit_addr,unsigned char dat)
{
    start_i2c();
    writebyte_i2c(s);
    waitack_i2c();
    writebyte_i2c(unit_addr);
    waitack_i2c();
    writebyte_i2c(dat);
    waitack_i2c();
    end_i2c();
	//delay(10);
}
unsigned char read_i2c(unsigned char s,unsigned char unit_addr)
{
    unsigned char dat;
    start_i2c();
    writebyte_i2c(s);
    waitack_i2c();
    writebyte_i2c(unit_addr);
    waitack_i2c();
    start_i2c();
    writebyte_i2c(s+1);
    waitack_i2c();
    dat=readbyte_i2c();
	waitack_i2c();
    end_i2c();
    //return (s==0x09)?((int)(5*dat/255.0*100+0.5)):dat;
	return dat;
}
void delay_i2c()
{
 	_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();_nop_();
}
//////////////////////////////////////////////////////////////////////////28byj-48/////////////////////
void byj(unsigned char right,unsigned int anglea,unsigned char delaybai)
{
	unsigned char bjright[]={0x08,0x0c,0x04,0x06,0x02,0x03,0x01,0x09};
	unsigned char bjleft[]={0x09,0x01,0x03,0x02,0x06,0x04,0x0c,0x08};
	unsigned char i;
	unsigned int ii,angle=8*anglea;			  //8*8内一圈，8*8*64外一圈，内一圈即5.625°  ，一个8就是0.703125°
	for(ii=0;ii<angle;ii++)
	{
		if(right==1)
		{
			for(i=0;i<8;i++)			  
			{
				P1=bjright[i];
				delay100us(delaybai);
			}
		}
		else if(right==0)
		{
			for(i=0;i<8;i++)			  
			{
				P1=bjleft[i];
				delay100us(delaybai);
			}
		}
	}
}
void delay100us(unsigned char b)   //误差 -0.173611111111us
{
    unsigned char a;
    for(;b>0;b--)
        for(a=43;a>0;a--);
}
/////////////////////////////////ds18b20///////////
int read_dstemper()
{    
   unsigned char a,b,c=0;         
   int t;
   c=init_ds18b20();
   if(c)return 999; 
   delay(1);      
   ds_write(0xcc);   //跳过ROM操作命令
   ds_write(0x44);     //发送启动温度转换命令 
   c=init_ds18b20();
   if(c)return 999; 
   delay(1);        
   ds_write(0xcc);    //跳过ROM操作命令
   ds_write(0xbe);      //发送读温度寄存器命令
   a=ds_read();    //先读低八位
   b=ds_read();      //再读高八位
   t=b;        
   t<<=8;      //左移八位
   t=t|a;      //t为16位的数，使高八位为b的值，低八位为a的值  
   return t;    //返回温度值	 //若<0(为负数)则先temper=temper-1;temper=~temper;再*0.0625*100+0.5
}
unsigned char ds_read()
{
	unsigned int i=0,j;
	unsigned char bi,byte;  
	for(j=8;j>0;j--)
	{
		ds_out=0;
		i++; 				 //拉低1us
		ds_out=1;
		i++;i++;			
		bi=ds_out;					 //15us内读取
		byte=(byte>>1)|(bi<<7);		 //移位
		i=4;
		while(i--);
	}
	return byte;
}
void ds_write(unsigned char dat)
{
	unsigned char i,j;
	for(j=0;j<8;j++)
	{
		ds_out=0;					//拉低
		ds_out=dat&0x01;			//取最低位1
		i=6;						//延时60-120us
		while(i--);
		ds_out=1; 					//释放
		dat>>=1;
	}
}
unsigned char init_ds18b20()			   //ds18b20初始化
{
	int i=0;
	ds_out=0;
	delay(1);
	ds_out=1; 
	while(ds_out)
	{
		delay15us(4);		//等待60-210us后检测
		i++;
		if(i>5)
		{
			return 1;		   //初始化失败	  超时
		}	
	}
	return 0;
}
void delay15us(unsigned char a)   //误差 -0.894097222222us
{
    for(a=4;a>0;a--);
}
///////////////////////////////////////hc-sr04///////
unsigned int getdistance()	//接收超声并计算距离
{
        unsigned int ss;//用于记录测得的距离
				TMOD=0x01;
				startmodule();
        while(!echo);//当echo为高电平的时候，跳出循环
        TH0 = 0;
        TL0 = 0;
				TR0 = 1;//启动定时器0，开启计时
        while(echo);//echo不为0，即脉冲返回结束，计时结束
        TR0 = 0;//停止计时
        ss=((TH0 * 256 + TL0)/2)*3.4;//单位是xxx.xxcm  可*1.1修正		范围大约2cm-400cm
        TH0 = 0;
        TL0 = 0;
				return ss;
}
void startmodule() 		         //发射超声
  {
	  trig=1;			                     
	  delay(1);
	  trig=0;
  }
///////////////////////////////////////ds12c887////////////////////////////////
void write_ds12c887(unsigned char add_ds12c887,unsigned char date_ds12c887)
{
    dsas=1;
	dsds=1;
	dsrw=1;
	P0=add_ds12c887;
	dsas=0;
	dsrw=0;
	P0=date_ds12c887;
	dsrw=1;
	dsas=1;
}
unsigned char read_ds12c887(unsigned char add_ds12c887)
{
    unsigned char ds_date;
    dsas=1;
	dsds=1;
	dsrw=1;
	P0=add_ds12c887; 
	dsas=0;
	P0=0XFF;
	dsds=0;
	ds_date=P0;
	dsds=1;
	dsas=1;
	return ds_date;						  
}

/////////////////////////////////////////1602/////////////////////////////////////
void init_1602()	//初始化		 
{
	rw_1602=0;			 //写
 	write_1602(0x38,0);	 //液晶设置不判忙模式
	delay(15);
	write_1602(0x38,0);
	delay(5);
	write_1602(0x0c,0);	 //光标设置0000 1dcb	 d:1:开 0:关 c:1:开光标 0:关光标 b:1:闪烁 0:不闪烁 
	write_1602(0x06,0);	//0000 01ns   n:1:每次指针加一（光标后移）0：减一  s:整屏左移（n=1）
}
void write_1602(unsigned char order_data,char i)  //i==1:data,i==0:order   //写 数据1 命令0
{
	   e_1602=0;								  //write_1602(0x80,0);指针(光标)指向一行一个(一行80----80+27;;二行80+40------40+27)
	   rs_1602=i;								   //0x01清屏	 0
	   P0=order_data;
	   e_1602=1;								   //'1' '2' 'd' 'b'  1  显示相应字符,其他的查看手册
       delay(1);									//0x30+2  xianshi 2
       e_1602=0;
}

//////////////////////////////数码管//////////////////////////////
void smg(unsigned char w,unsigned char d)	   //位 段
{
	smg_w(w);
	smg_d(d);
	delay(1);
	smg_w(8);
	smg_d(11);
	_nop_();
}
void smg_w(unsigned char i)
{
	unsigned char smw[]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0x00,};
	wei=1;
	P0=smw[i];
	wei=0;
}
void smg_d(unsigned char i)
{
	unsigned char smd[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0xff,0xbf,};//12:  -
	duan=1;
	P0=smd[i];
	duan=0;
}
///////////////////////////hc595////////////////////////////
void hc595(unsigned char m)
{
	unsigned char a;
	sck_hc595=0;
	for(a=0;a<8;a++)
	{
	 	lck_hc595=0;
		sdi_hc595=(m<<a)&0x80;
		lck_hc595=1;
	}
	sck_hc595=1;
	sdi_hc595=1;	
}
//////////////////////////////delay//////////////////////
void delay(unsigned int a)
{	
	unsigned int b;
	for(;a>0;a--)		  
		for(b=114;b>0;b--);
}