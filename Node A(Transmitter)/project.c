#include <lpc21xx.h>
#include "header.h" 

CAN1 msg1, msg2, msg3;

unsigned char ext0_flag = 0, ext1_flag = 0, ext2_flag = 0;
unsigned char headlight_flag = 0, Left_indicator_flag = 0, Right_indicator_flag = 0;

int main()
{
    // can1 initialise
    can1_init();

    // external interrupt init
    config_interrupts_init();
    config_vic_eints();

    // can initialisation
    msg1.rtr   = 0;
    msg1.ff    = 0;
    msg1.dataA = 0;
    msg1.dataB = 0;

    msg2.rtr   = 0;
    msg2.ff    = 0;
    msg2.dataA = 0;
    msg2.dataB = 0;

    msg3.rtr   = 0;
    msg3.ff    = 0;
    msg3.dataA = 0;
    msg3.dataB = 0;

    msg1.id  = 0x501;
    msg1.dlc = 1; 
    
    msg2.id  = 0x502;
    msg2.dlc = 1;
    
    msg3.id  = 0x503;
    msg3.dlc = 1;

    // logic
    while (1)
    {
        if (ext0_flag == 1)
        {
            ext0_flag = 0;

            if (headlight_flag == 0)
            {
                msg1.dataA = 0x10;
                can1_tx(msg1);
            }
            else
            {
                msg1.dataA = 0x11;
                can1_tx(msg1);
            }
        }

        if (ext1_flag == 1)
        {
            ext1_flag = 0;

            if (Right_indicator_flag == 0)
            {
                msg2.dataA = 0x12;
                can1_tx(msg2);
            }
            else
            {
                msg2.dataA = 0x13;
                can1_tx(msg2);
            }
        }

        if (ext2_flag == 1)
        {
            ext2_flag = 0;

            if (Left_indicator_flag == 0)
            {
                msg3.dataA = 0x14;
                can1_tx(msg3);
            }
            else
            {
                msg3.dataA = 0x15;
                can1_tx(msg3);
            }
        }	
    }
}
