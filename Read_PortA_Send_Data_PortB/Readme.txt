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
=============================
In PIC compilers, the program should inform which pins of which port will 
be used as input or output. The CCS C compiler allows to do this job 
automatically or not, as per the user's request. Since the #use fast_io(b) 
command is used in this example, the programmer himself will do the port 
input/output redirection (with set_tris_x() commands) in the program.
If one of the #use xxx_io() macros is not used in the CCS C compiler, 
the #use standard_io() command is considered to have been automatically 
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

In this application, the status of the buttons connected to the RA0, RA1, RA2, 
RA3, RA4 and RA5 pins of the A port is read and this information is transferred 
to the B port and sent to the LEDs connected to the B port.According to the 
Proteus drawing, when the RA0, RA1, RA2 and RA3 buttons are not pressed, logic-0 
information is generated for the inputs, and logic-1 information is generated 
when pressed. Because these buttons are active in logic-1 state. RA4 and RA5 
buttons are active in logic-0 state.For this reason, when button is not pressed 
at the first moment, RB4 and RB5 Leds turn on, all other leds turn off.When the 
RA0, RA1, RA2 and RA3 buttons are pressed, the corresponding output LEDs on the 
B port will turn on. Pressing the RA4 and RA5 buttons will turn off the LEDs on 
the relevant output.

In this program, with the #byte portb = 0x06 command, the word "portb" is assigned 
to the address of the PORTB register of the PIC16F877 controller. In other words, 
the compiler will now write the value of the portb variable to the location of the 
PORTB register of the PIC controller, which is at address 0x06. Thus, by assigning 
a value to the portb variable, a value can be sent directly to the output of port B.
An 8-bit integer type global object named read_input_a is defined in the program.
After the information is read from port A, the value is assigned to this variable.
set_tris_a (0xFF); With the command, the pins of the A port are set as complete input.
set_tris_b (0x00); With the command, the pins of the B port are set as complete output.

In the main function, at first read_input_a = input_a (); With command, input values 
of all pins of A port were read. read_input_a = read_input_a & 0b00111111; With the 
command, the last 2 most significant bits of the read_input_a variable are masked(reset).
This is done by bitwise (&) processing the number 0b00111111 of the read_input_a variable.
read_input_a = read_input_a & 0b00111111; //The first two unused pins of port B are masked
Port A is 6 bits. The information sent to the B port is 8 bits.Therefore, the state of the 
last 2 most significant bits of the read_input_a variable does not depend on the A port.
These bits are always reset by masking. Thus, the LEDs connected to the B port are prevented 
from turning on. Then portb = read_input_a; The command assigned the content of the read_input_a 
variable to the portb.

The program has proteus drawings. It can be run by inserting the hex code 
of the program into it.

Good work and Best Regards.