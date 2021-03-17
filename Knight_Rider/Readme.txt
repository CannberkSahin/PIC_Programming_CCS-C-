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

It is also specified in the program which ports and pins will be input or 
output. set_tris_b(0x00); With statement, port B is routed as complete exit.
0x00 in the command means in hexadecimal base. If we wanted to write it as a 
binary, we would write 0b00000000. 

In the program, output_b(0x00); With the command, the outputs of the B port 
are reset. Thus, with the reset made when the PIC is first energized, 
precautions are taken against the possibility that all of the register
contents are zero. 

Knight Rider circuit is based on the principle that the LEDs connected to the 
controller output are turned on and off sequentially and this cycle returns to 
the beginning.For this example, 8 red LEDs are connected to the controller's port.
An infinite loop has been created with the while (1) command. 8-bit integer 
variables named i and led are defined in the program. In the beginning, the value 
1 was assigned to the led variable. The binary value of 1 is 00000001.Then a
for(i = 0; i <8; ++ i) loop was created. With this command, it is stated that the 
loop in which the variable i will start from zero will continue as long as 
value of the i variable is less than 8, and the value of i will increase by 1 
at the beginning of each cycle. Output_b (led) in the loop; With the command, 
led = 1 value was sent to the B port. The 8-bit binary expansion of 1 is 0b00000001.
So the LED connected to the RB0 pin will turn on. After this command led = led << 1; 
With the command, the value of the led variable has been shifted one bit to the left.
0b00000001 -> 0b00000010 -> 0b00000100 -> 0b00001000 -> 0b00010000 etc.
Delay_ms (100) to see if the LEDs are on and off; command, a delay of 100 milliseconds 
was given. the loop will increase the value of i and go back to the beginning.
When the value of i reaches 8, the loop will exit. LED = 0x80 to start the lighting 
of the LEDs from the last LED connected to the RB7 pin. command, the value 0x80, 
ie 0b10000000 as binary, has been loaded to the led variable. Then output_b (led); 
This value was sent to the B port with command and the LED connected to the RB7 port 
was turned on. In the second for loop, the LED variable value is shifted to the right 
this time, and the turn on sequence of the LEDs is in the opposite direction.
Other commands are the same as the first for loop. The program will run this way forever.

The program has proteus drawings. It can be run by inserting the hex code 
of the program into it.

Good work and Best Regards.