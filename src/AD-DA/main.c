#include <reg52.h>
#include "eboard.h"
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define somenop() _nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_()
#define  WRITEADDR 0x90    //写地址
#define  READADDR  0x91    //读地址

sbit SCL=P2^1;
sbit SDA=P2^0;

void I2C_Start()     //起始
{
   SCL=1;
   somenop();
   SDA=1;
   somenop();
   SDA=0;
   somenop();
   SCL=0;
   somenop();
}
void I2C_Stop()      //终止
{  
   SDA=0;
   somenop();
   SCL=1;
   somenop();
   SDA=1;
   somenop();
}
void I2C_SendByte(uchar dat)   //发送一个字节
{
   uchar i,j,b=0;
   for(i=0;i<8;i++)
   {    
       SCL=0;  
       somenop();   
       SDA=(bit)(dat&0x80);     //每次取最高位进行发送
       dat<<=1;        //从最高位开始发送，左移使每一位逐渐成为最高位
       SCL=1;          //上升沿时发送数据
       somenop();      
   }
   SCL=0;
   somenop(); 
   SDA=1;     
   somenop();
   SCL=1;
   _nop_();
   while((SDA==1)&&(j<250))  j++;  //等待应答，也就是等待从设备把SDA拉低
   SCL=0;
   _nop_();   
}
uchar I2C_ReadByte()     //读一个字节
{
   uchar i,dat=0;
   SCL=0;         //此处也可以不置低，因为起始和发送一个字节之后SCL都是0
   somenop();
   SDA=1;      //拉高准备数据读取
   _nop_();
   for(i=0;i<8;i++)   //读取8位数据
   {
      SCL=1;
      somenop();
      dat<<=1;
      if(SDA==1)
         dat=dat|0x01;
      somenop();
      SCL=0;     //下降沿时读取数据
      somenop();
    }
    return dat;
}


void Pcf8591SendByte(uchar channel)
{   
    I2C_Start();   
    I2C_SendByte(WRITEADDR);        //发送写器件地址
    I2C_SendByte(0x40|channel);     //发送控制寄存器
    I2C_Stop();
}

uchar Pcf8591ReadByte()
{
    uchar num;
    I2C_Start();
    I2C_SendByte(READADDR);      //发送读器件地址
    num=I2C_ReadByte();          //读取数据
    I2C_Stop();                  //结束总线
    return num;
}
/******************************************************************* 
DAC 变换, 转化函数                
*******************************************************************/  
void DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)  
{  
   I2C_Start();                //启动总线  
   I2C_SendByte(sla);            //发送器件地址  
   I2C_SendByte(c);              //发送控制字节  
   I2C_SendByte(Val);            //发送DAC的数值     
   I2C_Stop();           //结束总线  
}  

void main()
{
  uint adNum,ad;
  float value;
	uchar dat[6];
	
  init_1602();
  while(1)
  {
		P0=0xff;
		Pcf8591SendByte(0);      //使用通道0
    /*adNum一定是0到255之间的一个数，因为pcf8591是8位的AD/DA芯片，所以输出的范围为00000000到11111111，即0到255*/
		ad=Pcf8591ReadByte();   //读出数值
		
    /*将adNum转换成电压值，单片机的电压为5V，则电位器的电压为0到5V，用0到255表示0到5V，则每一个1代表5/255V，即0.01953V*/
    value=ad*0.01953;  //转为电压值
    adNum=value*100;        //保留两位小数，以便显示出来
		

    dat[0]=adNum/1000;
    dat[1]=adNum%1000/100;
    dat[2]='.';
    dat[3]=adNum%100/10;
    dat[4]=adNum%10;
    dat[5]='V';
		
		write_1602(0x80+8,0);
		write_1602(0x30+dat[0],1);
		write_1602(0x30+dat[1],1);
		write_1602(dat[2],1);
		write_1602(0x30+dat[3],1);
		write_1602(0x30+dat[4],1);
		write_1602(dat[5],1);
		
		DACconversion(WRITEADDR,0x40,ad);
    }
}
