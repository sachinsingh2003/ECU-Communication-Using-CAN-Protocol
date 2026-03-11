#include<LPC21XX.H>
#include"header.h"
extern CAN1 msg1,msg2,msg3;
extern unsigned char ext0_flag,ext1_flag,ext2_flag;
extern unsigned char headlight_flag,Left_indicator_flag,Right_indicator_flag;
void EXT0_Handler(void)__irq
{
	ext0_flag=1;
	headlight_flag=!headlight_flag;
	EXTINT|=0X01;
	VICVectAddr=0;
}
void EXT1_Handler(void)__irq
{
	ext1_flag=1;
	Right_indicator_flag=!Right_indicator_flag;
	EXTINT|=0X02;
	VICVectAddr=0;
}
void EXT2_Handler(void)__irq
{
	ext2_flag=1;
	Left_indicator_flag=!Left_indicator_flag;
	EXTINT|=0X04;
	VICVectAddr=0;
}
void config_interrupts_init(void)
{
	PINSEL1|=0X01;//EXT0 P0.16
	PINSEL0|=0X0000C0C0;// EXT1 -->P0.3, EXT2-->P0.7
	//external intterupts configuration
	EXTMODE|=0X07;
	EXTPOLAR=0;
}
void config_vic_eints(void)
{
	VICIntSelect=0;//all irq
	//VIC SLOT0
	VICVectCntl0=(14)|(1<<5);
	VICVectAddr0=(unsigned int)EXT0_Handler;
	//VIC SLOT1
	VICVectCntl1=(15)|(1<<5);
	VICVectAddr1=(unsigned int)EXT1_Handler;
	//VIC SLOT2
	VICVectCntl2=(16)|(1<<5);
	VICVectAddr2=(unsigned int)EXT2_Handler;
	//ENABLING INTERRUPTS IN VIC PERIPHERIRAL
	VICIntEnable|=(1<<14)|(1<<15)|(1<<16);
}
