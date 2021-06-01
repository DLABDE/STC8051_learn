#include <reg52.h>
#include "eboard.h"
#include <intrins.h>

#define uchar unsigned char
#define uint unsigned int
#define somenop() _nop_(),_nop_(),_nop_(),_nop_(),_nop_(),_nop_()
#define  WRITEADDR 0x90    //д��ַ
#define  READADDR  0x91    //����ַ

sbit SCL=P2^1;
sbit SDA=P2^0;

void I2C_Start()     //��ʼ
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
void I2C_Stop()      //��ֹ
{  
   SDA=0;
   somenop();
   SCL=1;
   somenop();
   SDA=1;
   somenop();
}
void I2C_SendByte(uchar dat)   //����һ���ֽ�
{
   uchar i,j,b=0;
   for(i=0;i<8;i++)
   {    
       SCL=0;  
       somenop();   
       SDA=(bit)(dat&0x80);     //ÿ��ȡ���λ���з���
       dat<<=1;        //�����λ��ʼ���ͣ�����ʹÿһλ�𽥳�Ϊ���λ
       SCL=1;          //������ʱ��������
       somenop();      
   }
   SCL=0;
   somenop(); 
   SDA=1;     
   somenop();
   SCL=1;
   _nop_();
   while((SDA==1)&&(j<250))  j++;  //�ȴ�Ӧ��Ҳ���ǵȴ����豸��SDA����
   SCL=0;
   _nop_();   
}
uchar I2C_ReadByte()     //��һ���ֽ�
{
   uchar i,dat=0;
   SCL=0;         //�˴�Ҳ���Բ��õͣ���Ϊ��ʼ�ͷ���һ���ֽ�֮��SCL����0
   somenop();
   SDA=1;      //����׼�����ݶ�ȡ
   _nop_();
   for(i=0;i<8;i++)   //��ȡ8λ����
   {
      SCL=1;
      somenop();
      dat<<=1;
      if(SDA==1)
         dat=dat|0x01;
      somenop();
      SCL=0;     //�½���ʱ��ȡ����
      somenop();
    }
    return dat;
}


void Pcf8591SendByte(uchar channel)
{   
    I2C_Start();   
    I2C_SendByte(WRITEADDR);        //����д������ַ
    I2C_SendByte(0x40|channel);     //���Ϳ��ƼĴ���
    I2C_Stop();
}

uchar Pcf8591ReadByte()
{
    uchar num;
    I2C_Start();
    I2C_SendByte(READADDR);      //���Ͷ�������ַ
    num=I2C_ReadByte();          //��ȡ����
    I2C_Stop();                  //��������
    return num;
}
/******************************************************************* 
DAC �任, ת������                
*******************************************************************/  
void DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)  
{  
   I2C_Start();                //��������  
   I2C_SendByte(sla);            //����������ַ  
   I2C_SendByte(c);              //���Ϳ����ֽ�  
   I2C_SendByte(Val);            //����DAC����ֵ     
   I2C_Stop();           //��������  
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
		Pcf8591SendByte(0);      //ʹ��ͨ��0
    /*adNumһ����0��255֮���һ��������Ϊpcf8591��8λ��AD/DAоƬ����������ķ�ΧΪ00000000��11111111����0��255*/
		ad=Pcf8591ReadByte();   //������ֵ
		
    /*��adNumת���ɵ�ѹֵ����Ƭ���ĵ�ѹΪ5V�����λ���ĵ�ѹΪ0��5V����0��255��ʾ0��5V����ÿһ��1����5/255V����0.01953V*/
    value=ad*0.01953;  //תΪ��ѹֵ
    adNum=value*100;        //������λС�����Ա���ʾ����
		

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
