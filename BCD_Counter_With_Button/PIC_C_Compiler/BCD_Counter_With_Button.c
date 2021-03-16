/******************************************************************************
*Project Name: BCD(Binary Coded Decimal) Counter With Button
*Engineer: Canberk SAHIN
*Project Microcontroller: PIC16F877
*Version: V1
*Create Date: 14.03.2021
*Update Date: 14.03.2021
*University: Bursa Technical University
*Revision: - 
******************************************************************************/
#include <BCD_Counter_With_Button.h>

//Define Macro
#define     button    pin_A0

int8 i = 1;  //Global variable 8 bit

void main()
{
   setup_psp(PSP_DISABLED);           //PSP unit is disabled
   setup_timer_1(T1_DISABLED);        //T1 unit is disabled
   setup_timer_2(T2_DISABLED, 0, 1);  //T2 unit is disabled
   setup_adc_ports(NO_ANALOGS);       //There is no analog input 
   setup_adc(ADC_OFF);                //ADC unit is disabled
   setup_CCP1(CCP_OFF);               //CCP1 unit is disabled
   setup_CCP2(CCP_OFF);               //CCP2 unit is disabled
   
   set_tris_a(0x01);   //RA0 pin set as input
   set_tris_b(0x00);   //Port B is set as output
   
   output_b(0x00);     //B port output pins are reset
   
   while(TRUE)
   {
      if(input(button)){ 
         delay_ms(15);  //15 ms delay to avoid button arc
         
         output_b(i);   //The value of 1 of the counter is loading to port B
         ++i;           //increase i value
         while(input(button)) /*It waits until the button is not pressed */
            ; //Null statement
            
         if(10 == i)    //Returning to the beginning as there are 10 numbers
            i = 0;
      }
   }

}
