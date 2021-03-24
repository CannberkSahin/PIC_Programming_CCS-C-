/******************************************************************************
*Project Name: PMatrix Led Display
*Engineer: Canberk SAHIN
*Project Microcontroller: PIC16F877
*Version: V1
*Create Date: 21.03.2021
*Update Date: 21.03.2021
*University: Bursa Technical University
*Revision: - 
******************************************************************************/
#include <Matrix_Led_Display.h>

//Character information to be sent to Matrix Led (Arrays)
int A[]={0x03,0x75,0x76,0x75,0x03};
int B[]={0x00,0x36,0x36,0x36,0x49};
int C[]={0x41,0x3E,0x3E,0x3E,0x5D};
int D[]={0x00,0x3E,0x3E,0x3E,0x41};
int E[]={0x00,0xB6,0xB6,0xB6,0xBE};
int plus[]={0x77,0x77,0x41,0x77,0x77};
int d_arrow[]={0x6B,0x5D,0x00,0x5D,0x6B};

//Column selection function definition
int colselect(char s)
{
   switch(s){
      case 0: return (0x10); break;  //1st column active others passive (0001 0000)
      case 1: return (0x08); break;  //2nd column active others passive (0000 1000)
      case 2: return (0x04); break;  //3rd column active others passive (0000 0100)
      case 3: return (0x02); break;  //4th column active others passive (0000 0010)
      case 4: return (0x01); break;  //5th column active others passive (0000 0001)
   }
}

//Data Sending Function to Matrix Led Display
void send_char_matrix(char *ch, int count)
{
   int i,j,k;  //for loop
   
   for(i=1; i<count; ++i){ //Repeat loop for the character to appear on the display for a certain time
      for(k=0; k<10;  ++k){ //Scan Cycle (Scanning fo display)
         for(j=0; j<5; ++j){ //Choosing the columns in order
            output_c(colselect(j)); //Select column and send column value to C port
            
            output_b(ch[j]); //Send the line information of the letter to be displayed to port B
             
            delay_ms(1);     //1 millisecond delay
         }
      }
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
   
   set_tris_b(0x00);    //Port B is set as output
   set_tris_c(0x00);    //Port C is set as output
   
   while(TRUE)
   {
      send_char_matrix(A, 20);       //Printed the character A on the matrix display.
      send_char_matrix(B, 20);       //Printed the character B on the matrix display.
      send_char_matrix(C, 20);       //Printed the character C on the matrix display.
      send_char_matrix(D, 20);       //Printed the character D on the matrix display.
      send_char_matrix(E, 20);       //Printed the character E on the matrix display.
      send_char_matrix(plus 20);     //Printed the character plus character on the matrix display.
      send_char_matrix(d_arrow 20);  //Printed the character double arrow character on the matrix display.
   }

}
