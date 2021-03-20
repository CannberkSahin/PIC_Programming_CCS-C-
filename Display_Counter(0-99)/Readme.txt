Canberk ŞAHİN
E-Mail: canberk_cas@hotmail.com

In this reporisitory, basic level programs were written with PIC16xxx series 
microcontrollers produced by Microchip. The programs were drawn and simulated 
in the ISIS section of the Proteus program. Programs are written in the CCS C 
compiler and in the C language. Thus it provides a basis for understanding 
embedded systems.

The header file of the controller that will be used first while 
writing the program has been defined (#include <16f877.h>)
#include <16fxxx.h> this command must be in every program.
If you are using the PIC16F877A controller in your application, 
you have to change the header file to 16F977A.h.Do not forget 
to change the title file name with the same logic for other controller 
models.

#include <16f877.h>
===================
Then, definitions of configuration bits related to the controller 
used are specified. This command should be in every program. 
The CCS C compiler has included these commands in a header file 
identical to the filename to avoid confusion. If you create the 
project from the wizard tab, this header file comes automatically.
In the program we wrote, this file is #include <Led_Blinking_877.h>.
Configuration macros are available in this file. The configuration 
macros used in the project are as follows:

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES XT                       //Crystal or ceramic resonator (Xtal)
#FUSES NOPROTECT                //No protection against reading to ROM memory
#FUSES NOPUT                    //No Power Up Timer. Defines if PUT is not desired
#FUSES NOWRT                    //Program memory not write protected
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOCPD                    //No Code Protected Data. Used when protection of EEPROM memory is not requested

#use delay(crystal=20000000)    //Oscillator frequency used for the delay function
============================
#use delay (crystal = 20000000) macro is used in delay commands (delay_ms() etc.)
used in the program to let the compiler know the oscillator frequency used.

#use fast_io(b)                 //Port processing commands are valid for B port
#use fast_io(a)                 //Port processing commands are valid for A port
=============================
In PIC compilers, the program should inform which pins of which port will 
be used as input or output. The CCS C compiler allows to do this job 
automatically or not, as per the user's request. Since the #use fast_io(b)
and #use fast_io(a) command are used in this example, the programmer himself 
will do the port input/output redirection (with set_tris_x() commands) in 
the program. If one of the #use xxx_io() macros is not used in the CCS C 
compiler,the #use standard_io() command is considered to have been automatically 
used by the compiler.Thanks to this command, the program does not need to 
declare which port will input which port will be output. Because the compiler
automatically redirects ports as input and output according to the commands 
used. 

After the necessary pre-definitions are completed, the main function 
part is written in the program. The PIC16F877 controller contains various 
hardware units (ADC, EEPROM, CCP etc.). As a result, the same pin can 
have many functions. In order to prevent unused pin features from creating 
unwanted effects in the program while writing a program, unused features 
should be disabled with program commands. For this reason, hardware units 
that are not used at the beginning of the main function have been made passive.

It is also specified in the program which ports and pins will be input or 
output. set_tris_b(0x00); With statement, port B is routed as complete exit.
0x00 in the command means in hexadecimal base. If we wanted to write it as a 
binary, we would write 0b00000000. set_tris_a (0xFC); With the command, RA0, 
RA1 pins and other A port pins are input. FC = (0b1111 1100).

In this example, a counter that counts from 0 to 99 is made using a dual 
integrated display.7 information pins are required for single displays.
For example, a total of 28 information sending pins are required for a 4 digit display. 
This event occupies almost all pins of most controllers. Therefore, in order to run 
more than one display, the displays are fed with the same information line, but the 
displays are activated sequentially. For example, to see the number 25 on the display, 
first display is activated and "2" information is sent to the information line. 
Then 1st display is passive, 2nd display is activated and "5" information is sent to 
the information line. The image obtained in this way may not be completely clear. 
The reason for this is that the other display is active before the phosphor layers of 
the segments on the display are fully illuminated. To eliminate this problem, a "scanning" 
process is performed. In the scanning process, each display is fed with the same information 
for a short time and then it is passed to the other display. If this process is done more 
than 16 times a second, the human eye cannot distinguish between the on and off of the LEDs.
In this example, the scanning process in a dual integrated common cathode display is shown.
In the program, it is stated that after general definitions such as determining the oscillator 
frequency used for the controller header file configuration settings delay function, port 
forwarding with #use fast_io (a), #use fast_io (b) commands will be done with program commands 
rather than automatically. As seen in the circuit diagram, the dual display has two selection pins. 
The pin that chooses the first display is connected to the RA0 pin and the pin that chooses the 
second display is connected to the RA1 pin. Macros to replace these pins have been defined for 
convenience when writing the program. With the commands #define display_1 pin_a0, #define display_2 pin_a1 
and #define button pin_a2, the RA0 pin of the PIC controller is synchronized with the word "display_1" 
and the RA1 pin with the word "dsiplay_2" and the RA2 pin with the word "button". char ones = 0, tens = 0, 
num = 0; Global variables are assigned a zero value as the first defined value with commands.
The ones and tens variables defined in the character type are to hold the value of the ones and tens 
places of the number to be counted. The "num" variable also represents the whole number to be displayed 
on the display. output_low (display_1); , output_low (display_2); With the commands, first and second 
displays are disabled. In other words, RA1 pin and RA1 pin logic-0 are made. Therefore, since NPN type 
transistors will come with a white needle logic-0, the transistors will be insulated and since there 
will be no ground connection to the cathode ends of the common cathode display, the displays will be off.
num = 0; With the command, the first value of the number to be displayed on the display is assigned as 0.
An infinite loop is created with the while (true) command. ones = num% 10; tens = num / 10; With commands, 
the ones and tens digits of the number to be displayed in dsiplay are calculated. When calculating the 
ones digit, modal division is used. This gives the remainder of the num variable divided by 10.
This means the units digit of the num variable. To calculate the tens place of the variable num, the 
variable num is divided by 10. The full part of the partition value in this operation gives us the tens 
digit of the num variable. Then output_high (dsiplay_2); With the command, RA1 pin output is made logic-1, 
so the Q2 transistor is switched on. When Q2 is switched on, a short circuit occurs between the collector 
and the emitter and the cathode end of the display on the right is connected to the chassis.
So the display on the right is active. The active dsiplay e output_b (digit [ones]); The units digit of 
the number to be displayed with the command was sent, followed by delay_ms (5); a 5 millisecond delay 
was applied with the command. Then output_low (dsiplay_2); With the command, the second display is passive.
Then output_high (display_1); With command, the first display is activated. This is called scanning.
output_b (digit [tens]); Tens digit of the number is shown in the first display with the command. 
Again, a certain time delay is given and output_low (display_1); made passive with command. In this way, 
a first display and a second display are activated at a certain period of time and the necessary information 
is sent to scan. It is tested whether the "increase" button is pressed with the if (input (button)) command.
Unless the button is pressed, logic-0 information is sent to the RA2 input, and logic-1 information is sent 
to the input when the button is pressed. Therefore, when the "increase" button is pressed, the input (button) 
command will return with 1 information. In other words, the command will take the form of if (1) and since 
the condition will be accepted as true, if command operations will be performed.If the result of the transaction 
was 0, the condition would not be accepted and the commands under the if statement would not be executed. 
delay_ms (10) in the if statement; command is to prevent arcs that occur when the button is pressed.
++ num; With the command, it is provided to increase the value of num variable by 1 at each press of the button.
if (num == 100) and num = 0; With the commands, when the value of the num variable becomes 100, the variable 
is reset. Thus, counting will be between 0-99 and after 99, it will start from 0 again. While (inpu (button)) 
command is used to increase the value of the "num" variable by only 1 each time the button is pressed. 
When the button is pressed with this command, the command will take the form of while (1) and the commands 
in the while loop will be executed until the button is released. While loop commands are the same as display 
scan commands used at the beginning of the main function part of the program. Thus, when the button is pressed, 
the "num" value will increase by 1 and the new num value will appear on the display by scanning until you 
release the button. When the button is removed, the current value will appear on the display, thanks to the scan 
commands at the beginning of the while (true) loop. 

Important Note:
===============
When you try the circuit in the proteus program, you may not be able to simulate exactly.
While trying the circuit in the proteus program, give the display selection pins directly from the controller 
to the dsiplay.Do not use transistors in between. Normally, the transistor must be active for the desired
display to be active. Therefore, the output of the controller is made logic-1. Thus, the transistor starts 
conducting and the common cathode end of the display is connected to the chassis and thus the desired display 
is selected. However, if you want to simulate the protein without using a transistor, the control output 
should be inverted and logic-0 in order to make the desired display active.For example output_high (display_2); 
The command is inverted output_low (display_2); should be written in the form. This example is made in proteus 
and its codes are as in repo. However, if the circuit is to be tested in a real environment, the following 
codes should be written:

/******************************************************************************
*Project Name: Integrated Display Counter (0-99) Two Digits
*Engineer: Canberk SAHIN
*Project Microcontroller: PIC16F877
*Version: V1
*Create Date: 17.03.2021
*Update Date: 17.03.2021
*University: Bursa Technical University
*Revision: - 
******************************************************************************/
#include <Integrated_Display_Counter.h>

//Define Macros
#define display_1 pin_a0 //dispaly_1 expression equals pin_a0
#define display_2 pin_a1 //dispaly_2 expression equals pin_a1
#define button    pin_a2 //button expression equals pin_a2

//Define global variables
char ones=0, tens=0, num=0;

/*Data values for common cathode display*/
const int digit[10]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void main()
{
   setup_psp(PSP_DISABLED);           //PSP unit is disabled  
   setup_timer_1(T1_DISABLED);        //T1 unit is disabled
   setup_timer_2(T2_DISABLED, 0, 1);  //T2 unit is disabled
   setup_adc_ports(NO_ANALOGS);       //There is no analog input 
   setup_adc(ADC_OFF);                //ADC unit is disabled
   setup_CCP1(CCP_OFF);               //CCP1 unit is disabled.
   setup_CCP2(CCP_OFF);               //CCP2 unit is disabled.
   
   set_tris_a(0xFC);  //RA0, RA1 output, Other A port pins input FC=(1111 1100)
   set_tris_b(0x00);  //Port A is completely set as output
   
   output_low(display_1);  //1st Display in passive 
   output_low(display_2);  //2nd Display in passive
   
   while(TRUE)
   {
      ones=num%10;  //Calculate Ones digit
      tens=num/10;  //Calculate Tens digit
     
      output_high(display_2);  //2nd display is active
      output_b(digit[ones]);  //Numbers in the ones place were sent to the display
      delay_ms(5);            //5 mili second delay
      output_low(display_2);  //2nd Display in passive
      output_high(display_1); //1st Display is active
      output_b(digit[tens]);  //Numbers in the tens place were sent to the display
      delay_ms(5);            //5 mili second delay
      output_low(display_1);  //1st Display in passive
      
      if(input(button)){
         delay_ms(10);     //10 mili second delay
         
         ++num;  //increase num variable
         
         if(num==100){
             num=0;
         }
            
         ones=num%10;
         tens=num/10;
         
         while(input(button)){
      	    output_high(display_2);  //2nd display is active
            output_b(digit[ones]);  //Numbers in the ones place were sent to the display
            delay_ms(5);            //5 mili second delay
            output_low(display_2);  //2nd Display in passive
            output_high(display_1); //1st Display is active
            output_b(digit[tens]);  //Numbers in the tens place were sent to the display
            delay_ms(5);            //5 mili second delay
      output_low(display_1);  //1st Display in passive
         }
      }
   }
}

The program has proteus drawings. It can be run by inserting the hex code 
of the program into it. 

Good work and Best Regards.