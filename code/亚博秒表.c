#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
#define duan P0
#define  wei P2
 
sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit beep=P3^3;

uint hm=0,m=0,f=0;
uchar time_count=0;

uchar code table[] ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
uchar code table1[]={0xbf,0x86,0xdb,0xcf,0xe6,0xed,0xfd,0x87,0xff,0xef};
void delayms(uint xms)
{
	uint i,j;
	for(i=xms;i>0;i--)
		for(j=110;j>0;j--);
}

void start_time()
{
	ET0=1;
	EA=1;
	TR0=1;
}

void stop_time()
{
	ET0=0;
	EA=0;
	TR0=0;
}

void display()
{  while(1)
   {
	if(time_count==2)
	{
	hm++;
	time_count=0;
	}
	if(hm==10)
	{	
	    hm=0;
		m++;
	}
	if(m==60)
	{
		m=0;
		f++;
	}
	duan=table[hm];		
	wei=0x88;          delayms(5);			
	duan=table1[m%10];	
	wei=0x48;			delayms(5);
	duan=table[m/10];	
	wei=0x28;		   delayms(5);
	duan=table1[f];	
	wei=0x18;		   	delayms(5);
   	if(key2==0)
	break; 
	}    
}
void main()
{
	TMOD=0X01;
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	duan=0x00;
	while(1)
	{ 
	duan=table[hm];		
	wei=0x88;          delayms(5);			
	duan=table1[m%10];	
	wei=0x48;			delayms(5);
	duan=table[m/10];	
	wei=0x28;		   delayms(5);
	duan=table1[f];	
	wei=0x18;		   	delayms(5);
				

		//开始计时
		if(key1==0)
		{
			delayms(10);
			if(key1==0)
			{
				start_time();
				display();
				stop_time();
			}
		}

		//停止计时
		if(key3==0)
		{	
			hm=m=f=0;
		}
	}
}			


void timer() interrupt 1
{
	TH0=(65536-46080)/256;
	TL0=(65536-46080)%256;
	time_count++;
}			