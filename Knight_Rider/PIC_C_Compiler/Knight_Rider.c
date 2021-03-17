/******************************************************************************
*Project Name: Knight Rider Circuit With Led
*Engineer: Canberk SAHIN
*Project Microcontroller: PIC16F877
*Version: V1
*Create Date: 17.03.2021
*Update Date: 17.03.2021
*University: Bursa Technical University
*Revision: - 
******************************************************************************/
#include <Knight_Rider.h>

int8 i, led;      //Global variables of 8-bit data type

void main()
{

   setup_psp(PSP_DISABLED);           //PSP unit is disabled
   setup_timer_1(T1_DISABLED);        //T1 unit is disabled
   setup_timer_2(T2_DISABLED, 0, 1);  //T2 unit is disabled
   setup_adc_ports(NO_ANALOGS);       //There is no analog input 
   setup_adc(ADC_OFF);                //ADC unit is disabled
   setup_CCP1(CCP_OFF);               //CCP1 unit is disabled.
   setup_CCP2(CCP_OFF);               //CCP2 unit is disabled.
   
   set_tris_b(0x00);                  //Port B is completely out
   output_b(0x00);                    //B port output bits are all 0(zero) 
   
   while(TRUE)
   {
      led = 1; //0b00000001
      
      /*The LEDs will be turned on in order from top to bottom.*/
      for(i=0; i<8; ++i){
         output_b(led);   //led = 0b00000001
         led = led << 1;  //led = 0b00000010 (led variable value is shifted 1 bit left)
         delay_ms(100);   //100 mili second delay
      }
      
      led = 0x80;  //0b10000000
      output_b(led); //The last LED will stay on
      delay_ms(100);
      
      /*The LEDs will be turned on in order from bottom to top.*/
      for(i=0; i<7; ++i){ 
         led = led >> 1;  //led = 0b11111111
         output_b(led);   //led = 0b11111110 -> 0b11111100 -> 0b11111000 etc.
         delay_ms(100);   //100 mili second delay
      }
   }

}
