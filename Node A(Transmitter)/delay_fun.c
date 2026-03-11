#include<lpc21xx.h>
void delay_sec(unsigned int sec)
{
	T0PR = 15000000-1;
	T0PC = T0TC =0;
	T0TCR = 1;
	while(T0TC < sec);
	T0TCR = 0;
}
void delay_msec(unsigned int msec)
{
	T0PR = 15000-1;
	T0PC = T0TC =0;
	T0TCR = 1;
	while(T0TC < msec);
	T0TCR = 0;
}
