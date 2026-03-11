#include<lpc21xx.h>
#include"header.h"

//  Initialization function

void uart0_init(unsigned int baud)
{
	int result,pclk;
	int a[]={15,60,30};
	pclk = a[VPBDIV] * 1000000;    // convert MHz to Hz
	result = pclk / (16 * baud);
	PINSEL0 |= 0x5;
	U0LCR = 0x83;
	U0DLL = result&0xff;
	U0DLM = (result>>8)&0xff;
	U0LCR = 0x03;
	
}

// Transmission Function

#define THRE ((U0LSR>>5)&1)
void uart0_tx(unsigned char data)
{
	U0THR = data;
	while(THRE==0);
}

// Receiver Function

#define RDR (U0LSR&1)
unsigned char uart0_rx(void)
{
	while(RDR==0);
	return U0RBR;
		
}

// String Function

void uart0_string(char *ptr)
{
	while(*ptr != 0)
	{
		uart0_tx(*ptr);
		ptr++;
	}
}


// Integer Function

void uart0_integer(int num)
{
	int a[10],i=0;
	if(num==0)
	{
		uart0_tx('0'); return;
	}
	if(num<0)
	{
		num = -num;
		uart0_tx('-');
	}
	while(num>0)
	{
		a[i++]= num %10 + 48;
		num= num/10;
	}
	for(i=i-1;i>=0;i--)
	{
		uart0_tx(a[i]);
	}
}

// Binary Function

void uart0_binary(int num)
{
	int pos,temp;
	for(pos=7;pos>=0;pos--)
	{
		temp = num>>pos&1;
		uart0_tx(temp+48);
	}
}




