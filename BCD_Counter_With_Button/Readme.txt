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
binary, we would write 0b00000000. set_tris_a (0x01); With command, RA0 pin 
is set as input.

In the program, output_b(0x00); With the command, the outputs of the B port 
are reset. Thus, with the reset made when the PIC is first energized, 
precautions are taken against the possibility that all of the register
contents are zero. 

In this application, BCD (Binary Coded Decimal) application was made with 
LEDs connected to the B port (RB0, RB1, RB2, RB3). BCD numbers contain a 
4-bit binary equivalent for decimal numbers 0 to 9. When the circuit is started, 
decimal numbers from 0 to 9 increase each time the button is pressed and the BCD 
equivalents are displayed on the LEDs.
An infinite loop is created with while(1). With the if (input (button)) command, 
the button input, that is the RA0 input, is read and the if loop is enabled when 
the button is pressed, that is, when the RA0 input is logic-1.Therefore, the inside 
of the if command will be 1 and the commands below it will be processed. If the 
button is not pressed, commands under the if loop are skipped. Thus, the program 
will return empty unless the button is pressed.delay_ms (15); button arc is prevented 
with command.output_b (i); The value of i was sent to port b with the command. Thus, 
the LED connected to the RB0 pin of the b port will turn on. ++ i; The command increases 
the value of the variable i by 1. while (input (button)); With the command, the program 
does not exit this cycle until we release the button, preventing the counter from 
increasing by itself. In fact, the aim is to increase the BSD counter by only 1 when 
the button is pressed once. if (10 == i) -> i = 10; With the control statement, when 
the value of i is 10, the program has been enabled to return to the beginning. 
Hence the value of i becomes 0 and the counter starts over.

The program has proteus drawings. It can be run by inserting the hex code 
of the program into it. 

Good work and Best Regards.