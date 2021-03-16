/*****************************************************************************
*Project Name: Read port a and sent data to port b.
*Engineer: Canberk SAHIN
*Project Microcontroller: PIC16F877
*Version: V1
*Create Date: 16.03.2021
*Update Date: 16.03.2021
*University: Bursa Technical University
*Revision: -
******************************************************************************/
#include <Read_PortA_Send_Data_PortB.h>

//Define Macro
#byte portb = 0x06    //portb is initialized with the controller's B port register's address

//Define global varible 
int8 read_input_a;    //An 8-bit integer type global variable is defined.

void main()
{
   setup_psp(PSP_DISABLED);           //PSP unit is disabled
   setup_timer_1(T1_DISABLED);        //T1 unit is disabled
   setup_timer_2(T2_DISABLED, 0, 1);  //T2 unit is disabled
   setup_adc_ports(NO_ANALOGS);       //There is no analog input 
   setup_adc(ADC_OFF);                //ADC unit is disabled
   setup_CCP1(CCP_OFF);               //CCP1 unit is disabled
   setup_CCP2(CCP_OFF);               //CCP2 unit is disabled
   
   set_tris_a(0xFF);  //All pins of port A are input
   set_tris_b(0x00);  //All pins of port B are output
   
   output_b(0x00);    //B port pins reset

   while(TRUE)
   {
      read_input_a = input_a();  //Reading input of port A
      read_input_a = read_input_a & 0b00111111; //The first two unused pins of port B are masked
      portb = read_input_a;  //Output of B port is the value read from A port
   }

}
