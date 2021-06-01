#include<eboard.h>

sbit keyn=P2^0;
sbit keya=P2^2;
sbit keyb=P2^1;

unsigned char open=1;

void opendef(unsigned char a)//0:open  1:close
{
	if(open!=a)
	{
		byj(a,35,17);
		P1=0x00;
		open=a;
	}
}
void main()
{
	keyn=0;
	keya=0;
	keyb=0;
	
	while(1)
	{
	
		if((keyb==1)&&(keya==1)&&(keyn==1))
		{
			delay(100);
			if((keyb==1)&&(keya==1)&&(keyn==1))
			{
				while(((keyb==1)&&(keya==1)&&(keyn==1)));
				opendef(0);
				delay(500);
				opendef(1);
				
				keyb=0;
				keya=0;
				keyn=0;
			}
		}
		
		if(keyn==1)
		{
			delay(50);
			if(keyn==1)
			{
				while(keyn);
				opendef(0);
				delay(5000);
				opendef(1);
				
				keyn=0;
			}
		}
		
		if((keya==1)&&(keyb==0)&&(keyn==0))///////11111
		{
			delay(50);
			if((keya==1)&&(keyb==0)&&(keyn==0))
			{
				while(keya);
				delay(600);
				if((keya==1)&&(keyb==1)&&(keyn==0))//////111222
				{
					delay(50);
					if((keya==1)&&(keyb==1)&&(keyn==0))
					{
						while((keya==1)&&(keyb==1));
						delay(600);
						if((keya==1)&&(keyb==0)&&(keyn==0))///////1111111
						{
							delay(50);
							if((keya==1)&&(keyb==0)&&(keyn==0))
							{
								while(keya);
								delay(600);
								if((keya==0)&&(keyb==1)&&(keyn==0))///////22222
								{
									delay(50);
									if((keya==0)&&(keyb==1)&&(keyn==0))
									{
										while(keyb);
										opendef(0);
										delay(5000);
										opendef(1);
										
										keya=0;
										keyb=0;
										keyn=0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
}