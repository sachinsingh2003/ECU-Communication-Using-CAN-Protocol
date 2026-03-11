#include <lpc21xx.h>
#include "header.h" 
#define LED1 (1<<17)
#define LED2 (1<<18)
#define LED3 (1<<19)
#define BUZZER (1<<16)
CAN1 r1;
volatile unsigned char flag=0;
unsigned char Left_indicator_flag = 0, Right_indicator_flag = 0;
int main()
{
	unsigned int blink=0;
	unsigned long long int temp=0;
	IODIR0|=7<<17;
	IODIR0 |= BUZZER;
	lcd_init();
	uart0_init(9600);
	can1_init();
	config_vic_for_can1();
	uart0_string("uart initilised\r\n");
	lcd_cmd(0xc0);
	lcd_data('A');
//	lcd_string("lcd_initialised");
	lcd_cmd(0x80);
	lcd_cgram();
	while(1)
	{

		if(flag==1)
		{
			flag=0;blink=0;
			temp=r1.dataA|((unsigned long long int)r1.dataB<<32); 
			if(r1.id==0x501 && (temp==0x10))
			{
				IOSET0|=LED1;
				uart0_string("Headlight OFF\r\n");
				lcd_cmd(0x80);
				lcd_data(' ');				
			}
			else if(r1.id==0x501 && temp==0x11)
			{
				IOCLR0|=LED1;
				uart0_string("Headlight ON\r\n");
				lcd_cmd(0x80);
				lcd_data(2);
			}	
			else if(r1.id==0x502 && (temp==0x12))
			{
				IOSET0|=LED2;
				Right_indicator_flag=0;
				uart0_string("Right Indicator OFF\r\n");
				lcd_cmd(0x8f);
				lcd_data(' ');
			}
			else if(r1.id==0x502 && temp==0x13)
			{
				if(Left_indicator_flag)
				{
					IOSET0|=LED3;
					Left_indicator_flag=0;
				}
				uart0_string("Right Indicator ON\r\n");
				lcd_cmd(0x8f);
				lcd_data(0);
				IOCLR0|=LED2;
				Right_indicator_flag=1;
			}
			else if(r1.id==0x503 && temp==0x14)
			{
				IOSET0|=LED3;
				Left_indicator_flag=0;
				uart0_string("Left Indicator OFF\r\n");
				lcd_cmd(0x87);
				lcd_data(' ');
			}
			else if(r1.id==0x503 && temp==0x15)
			{
				if(Right_indicator_flag)
				{
					IOSET0|=LED2;
					Right_indicator_flag=0;
				}
				IOCLR0|=LED3;
				Left_indicator_flag=1;
				
				uart0_string("Left Indicator ON\r\n");
				lcd_cmd(0x87);
				lcd_data(1);
			}
		}
		if(Right_indicator_flag)
		{
			if(blink)
			{
				IOSET0|=LED2;
				IOSET0 = BUZZER;
				
			}
			else
			{
				IOCLR0|=LED2;
				IOCLR0 = BUZZER;
			}
			delay_msec(200);
			blink=!blink;
		}
		if(Left_indicator_flag)
		{
			if(blink)
			{
				IOSET0|=LED3;
				IOSET0 = BUZZER;
			}
			else
			{
				IOCLR0|=LED3;
				IOCLR0 = BUZZER;
			}
			delay_msec(200);
			blink=!blink;
		}
		else
		{
			IOCLR0 = BUZZER;
		}
	}
}
