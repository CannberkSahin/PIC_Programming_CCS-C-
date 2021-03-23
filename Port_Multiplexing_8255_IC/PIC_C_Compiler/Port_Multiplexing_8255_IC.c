/******************************************************************************
*Project Name: Port Multiplexing With 8255 IC
*Engineer: Canberk SAHIN
*Project Microcontroller: PIC16F877
*Version: V1
*Create Date: 21.03.2021
*Update Date: 21.03.2021
*University: Bursa Technical University
*Revision: - 
******************************************************************************/
#include <Port_Multiplexing_8255_IC.h>

//Define global variables
int8 data;

//Define a write function for 8255 IC
void _8255_write(char x, char info)
{
   switch(x){
      case 'r':              //If write to Register is selected
      output_a(0b00001101);  //Register write bits definition
      output_b(info);        //The information to be written is being sent
      break;
      
      case 'a':              //If write to port A is selected
      output_a(0b00000001);  //Writing to port A
      output_b(info);        //The information to be written is being sent
      break;
      
      case 'b':              //If write to port B is selected
      output_a(0b00000101);  //Writing to port B
      output_b(info);        //The information to be written is being sent
      break;
      
      case 'c':              //If write to port C is selected
      output_a(0b00001001);  //Writing to port C
      output_b(info);        //The information to be written is being sent
      break;
      
      default:               //null process
      break;
   }
}

//Define a read function for 8255 IC
int _8255_read(char x)
{
   switch(x){
      case 'r':              //If write to Register is selected
      output_a(0b00001110);  //Reading recorder value
      return (input_b());
      
      case 'a':              //Reading from port A is selected
      output_a(0b00000010);  //Register write bits definition
      return (input_b());    //The function returns this value
      
      case 'b':              //Reading from port B is selected
      output_a(0b00000110);  //Register write bits definition
      return (input_b());    //The function returns this value
      
      case 'c':              //Reading from port C is selected
      output_a(0b00001010);  //Register write bits definition
      return (input_b());    //The function returns this value
      
      default:               //null process
      break;
   }
}

void main()
{
   setup_psp(PSP_DISABLED);           //PSP unit is disabled  
   setup_timer_1(T1_DISABLED);        //T1 unit is disabled
   setup_timer_2(T2_DISABLED, 0, 1);  //T2 unit is disabled
   setup_adc_ports(NO_ANALOGS);       //There is no analog input 
   setup_adc(ADC_OFF);                //ADC unit is disabled
   setup_CCP1(CCP_OFF);               //CCP1 unit is disabled.
   setup_CCP2(CCP_OFF);               //CCP2 unit is disabled.
   
   _8255_write('r',0b10001001);       //A port is out, C port is in and B port is out
   _8255_write('a',0x00);             //A port is out, C port is in and B port is out.

   while(TRUE)
   {
      data = _8255_read('c');        //Reading port C
      _8255_write('a',data);         //The value read from the C port is written to the A port
   }

}
