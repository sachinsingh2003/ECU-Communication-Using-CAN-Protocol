#include<lpc21xx.h>
#include"header.h"
extern CAN1 r1;
extern unsigned char flag;
#define TCS (C1GSR>>3&1)
#define RBS (C1GSR&1)
void can1_init(void)
{
	unsigned int *ptr=(unsigned int *)0xE0038000;
    PINSEL1|=0x40000; //P0.25 RD1 PIN
	VPBDIV=1; //60MHZ
	C1MOD=1;//RESET MODE
	AFMR=0x02;//AF SETTING ON
	///AFSETTINGS///
	//-----------in keil can1 number 31,30,29 bits 001 and so on
	ptr[0]=0x25012502;//assign 0x501 and 0x502 s
	ptr[1]=0x25031000;//assign 0x503 and disable next slot;
	/*-------------on hardware-------------------------    */
//	ptr[0]=0x05010502;//assign 0x501 and 0x502 ids
//	ptr[1]=0x05030100;//assign 0x503 and disable next slot;
	SFF_sa=0x00;
	SFF_GRP_sa=0X08;
	EFF_sa=0X08;
	EFF_GRP_sa=0X08;
	ENDofTable=0X08;
	////////////////
	AFMR=0X00;
	C1BTR=0x001C001D;//Baud is 125Kbps
	C1MOD=0;//cancel reset mode	
	}
void can1_tx(CAN1 df)
{
	C1TID1=df.id;
	C1TFI1=(df.dlc<<16)|(df.rtr<<30)|(df.ff<<31);
	if(df.rtr==0)
	{
	C1TDA1=df.dataA;
	C1TDB1=df.dataB;
	}
	C1CMR=0x21;//Start Xmission &//select Txbuf1 for Xmission
	while(TCS==0);
}

void can1_rx_handler(void) __irq{
	flag=1;//further used in main func
	r1.id=C1RID;
	r1.dlc=(C1RFS>>16)&0xF;
	r1.rtr=(C1RFS>>30)&1;
	if(r1.rtr==0){
		r1.dataA=C1RDA;
		r1.dataB=C1RDB;
	}

	C1CMR=(1<<2);//RELEASE RECEIVER BUFFER
	VICVectAddr=0;
}

void config_vic_for_can1(void){
	VICIntSelect=0;//optional
	VICVectCntl2=26|(1<<5);
	VICVectAddr2=(unsigned int)can1_rx_handler;
	VICIntEnable=(1<<26);
	C1IER=1;//En CAN1 Rx Intr
}

