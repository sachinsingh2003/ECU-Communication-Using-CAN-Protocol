#include<lpc21xx.h>
#include"header.h"
extern CAN1 msg1,msg2,msg3;
extern unsigned char headlight_flag,Left_indicator_flag,Right_indicator_flag;
#define TCS (C1GSR>>3&1)
void can1_init(void)
{
  PINSEL1|=0x40000; //P0.25 RD1 PIN
	VPBDIV=1; //60MHZ
	C1MOD=1;//RESET MODE
	AFMR=2;
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
	//while(TCS==0);
}

//void can1_rx_handler(void) __irq{
//	r1.id=C1RID;
//	r1.dlc=(C1RFS>>16)&0xF;
//	r1.rtr=(C1RFS>>30)&1;
//	if(r1.rtr==0){
//		r1.dataA=C1RDA;
//		r1.dataB=C1RDB;
//	}
//	C1CMR=(1<<2);//*
//	flag=1;//further used in main func
//	VICVectAddr=0;
//}

//void config_vic_for_can1(void){
//	VICIntSelect=0;//optional
//	VICVectCntl2=26|(1<<5);
//	VICVectAddr2=(unsigned int)can1_rx_handler;
//	VICIntEnable=(1<<26);
//	C1IER=1;//En CAN1 Rx Intr
//}
