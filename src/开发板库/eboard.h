#ifndef _EBOARD_H
#define _EBOARD_H

#include<reg52.h>
#include<intrins.h>

sbit sdi_hc595=P1^0;
sbit lck_hc595=P1^4;
sbit sck_hc595=P2^3;

sbit duan=P2^5;
sbit wei=P2^6;

sbit rs_1602=P2^5;
sbit rw_1602=P2^6;
sbit e_1602=P2^4;

sbit dsds=P1^0;
sbit dsrw=P1^1;
sbit dsas=P1^2;
sbit dsirq=P3^2;

sbit trig=P2^0;
sbit echo=P2^1;

sbit ds_out=P2^2;

sbit scl=P2^1;
sbit sda=P2^0;


void smg_d(unsigned char i);
void smg_w(unsigned char i);
void smg(unsigned char w,unsigned char d);

void delay(unsigned int a);
void hc595(unsigned char m);

void init_1602();
void write_1602(unsigned char order_data,char i);

void write_ds12c887(unsigned char add_ds12c887,unsigned char date_ds12c887);
unsigned char read_ds12c887(unsigned char add_ds12c887);

void startmodule();
unsigned int getdistance();

int read_dstemper();
unsigned char ds_read();
void ds_write(unsigned char dat);
unsigned char init_ds18b20();
void delay15us(unsigned char);

void byj(unsigned char right,unsigned int anglea,unsigned char delaybai);
void delay100us(unsigned char b);

void start_i2c();
void end_i2c();
void waitack_i2c();
void writebyte_i2c(unsigned char dat);
unsigned char readbyte_i2c();
void write_i2c(unsigned char s,unsigned char unit_addr,unsigned char dat);
unsigned char read_i2c(unsigned char s,unsigned char unit_addr);
void delay_i2c();
#endif /* _EBOARD_H */