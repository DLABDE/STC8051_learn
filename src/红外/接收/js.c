#include<reg52.h>
#include<intrins.h>
sbit js=P3^2;
sbit led=P2^0;

int jss=0;
void delay1s(void)   //误差 -0.000000000227us
{
    unsigned char a,b,c;
    for(c=13;c>0;c--)
        for(b=247;b>0;b--)
            for(a=142;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}

void main()
{
	EA=1;              //允许CPU响应所有中断 
	IT0=1;             //设外部中断0的响应模式为边沿触发 
	EX0=1;             //允许中断0产生中断
	delay1s();
	if(jss==15||16||17||18||19||20||21||22||13||24||25)
	{
		led=1;
	}
	if(jss==35||36||37||38||39||40||41||42||43||44||45)
	{
		led=0;
	}


}

void zhongduan() interrupt 0 using 0       //声明中断处理函数，由于是外部中断，所以 interrupt X 里X的值是 0 
	{ 
		jss++;  //CPU响应中断后会跑来这里执行
	}