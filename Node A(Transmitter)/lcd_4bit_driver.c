#include<lpc21xx.h>
#include"header.h"
void lcd_data(unsigned char data)
{
//------ Higher Nibble------
	unsigned int temp;
	IOCLR1 = 0x00FE0000;
	temp = (data&0xF0)<<16;

	IOSET1 = temp;
	IOSET1 = 1<<17;        //RS = 1
	IOCLR1 = 1<<18;				//RW = 0
	IOSET1 = 1<<19;       //EN = 1
	delay_msec(2);
	IOCLR1 = 1<<19;       //EN = 0

	//------ Lower Nibble------
	IOCLR1 = 0x00FE0000;
	temp = (data&0x0F)<<20;
	IOSET1 = temp;
	IOSET1 = 1<<17;        //RS = 1
	IOCLR1 = 1<<18;				//RW = 0
	IOSET1 = 1<<19;       //EN = 1
	delay_msec(2);
	IOCLR1 = 1<<19;       //EN = 0
	
}
void lcd_cmd(unsigned int cmd)
{
	//------ Higher Nibble------
	unsigned int temp;
	IOCLR1 = 0x00FE0000;
	temp = (cmd&0xF0)<<16;
	IOSET1 = temp;
	IOCLR1 = 1<<17;        //RS = 1
	IOCLR1 = 1<<18;				//RW = 0
	IOSET1 = 1<<19;       //EN = 1
	delay_msec(2);
	IOCLR1 = 1<<19;       //EN = 0

	//------ Lower Nibble------
	IOCLR1 = 0x00FE0000;
	temp = (cmd&0x0F)<<20;
	IOSET1 = temp;
	IOCLR1 = 1<<17;        //RS = 1
	IOCLR1 = 1<<18;				//RW = 0
	IOSET1 = 1<<19;       //EN = 1
	delay_msec(2);
	IOCLR1 = 1<<19;       //EN = 0
}
void lcd_string(char *ptr)
{
	while(*ptr != 0)
	{
		lcd_data(*ptr);
		ptr++;
	}
}

void lcd_integer(int num)
{
	int a[10],i;
	if(num==0)
	{
		lcd_data('0'); return;
	}
	if(num<0)
	{
		num = -num;
		lcd_data('-');
	}
	while(num>0)
	{
		a[i++]= num %10 + 48;
		num= num/10;
	}
	for(i=i-1;i>=0;i--)
	{
		lcd_data(a[i]);
	}
}

void lcd_float(float num, int precision)
{
    int int_part;
    float frac_part;
    int i;

    /* Handle negative number */
    if(num < 0)
    {
        lcd_data('-');
        num = -num;
    }

    /* Integer part */
    int_part = (int)num;
    lcd_integer(int_part);

    lcd_data('.');   // decimal point

    /* Fractional part */
    frac_part = num - int_part;

    for(i = 0; i < precision; i++)
    {
        frac_part *= 10;
        lcd_data((int)frac_part + '0');
        frac_part -= (int)frac_part;
    }
}

void lcd_cgram(void)
{
	int i;
	unsigned char a[8] = {0x0,0xA,0xA,0x0,0x0,0x11,0xE,0x0};
	lcd_cmd(0x40);
	
	for(i=0;i<8;i++)
	{	
		lcd_data(a[i]);
	}
}

void lcd_init()
{
	IODIR1 = 0x00FE0000;
	lcd_cmd(0x02);
	lcd_cmd(0x28);       // select 1 and 2 and row of lcd
	lcd_cmd(0x0e);			 // enable cursor
	lcd_cmd(0x01);			 // clear screen
}
