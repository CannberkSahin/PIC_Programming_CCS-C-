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
#use fast_io(c)                 //Port processing commands are valid for C port
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

Matrix Led Display
==================
What is LED matrix? Led matrix is a dot matrix of large display, low resolution 
value and is useful for both industrial or commercial displays as well as for 
hobbyist human interface machines. In contains a 2-D diode matrix which have the 
cathode joined in rows and anode in columns. In this LED matrix each can be control 
individually by controlling the electricity through each pair of columns or rows 
diodes. These matrix are very popular matrix by means of displaying information it, 
allows the static and animated images and text.

Types of LED Matrix:
--------------------
There are so many types are LED matric have been used for industrial and commercial
purposes, some of which are discussing in this article with respect to structure.

8*8 dot Matrix
5*7 dot Matrix
128*16 Two lined
128*32 Four lined
128*64 Eight lined

8*8 dot Matrix:
---------------
In dot matrix multiple diodes are connecting together in rows and columns, this is 
done to minimize the number of pins required to drive the dot light emitting diodes. 
Suppose in 8*8 dot matrix there would be 64 I/O pins for displaying each diode pixel. 
For making 8*8 dot matrix all the anodes are connecting together in rows R1 to R8, 
similarly the cathodes are connected together in columns C1 to C8, by doing this the 
required number of I/O pins have reduced by 16.According to the figure each LED is 
addressed to its row and column number. If R5 is pulled high and C4 pulled low, then 
the LED in fifth row and fourth column would be high, similarly the characteristics 
can also be displayed by scanning of each row and column.

5*7 dot Matrix:
---------------
A 5*7 LED matrix have 5 rows and 7 columns of light emitting dioses, which are connecting 
together for making this shown is figure in 3. According to the figure we want to display 
an alphabet word A then first we pulled high the column C1 and pulled low the other columns 
by blocking their ground paths. Now the C1 is pulled high and need to turn on the LEDs of 
rowsR2 to R7 of this column. This is done by the applying the forward bias voltage to these 
rows. Next select the column C2 and deselect the other column and apply the forward bias 
voltage across R1 and R5, and so on.

Construction of dot Matrix:
---------------------------
The construction of this display is very simple if you want to make your own prototype 
display then the diodes are just solder on Vero board or premade double or single sided board. 
Suppose we want a construct a prototype 8*8 dot matrix display, then we have  required 64 light 
emitting diodes. These diodes are solder on overboard or single sided board. 
The positive end of one diose is connected to other positive end of the diode for making the rows, 
similarly the 8 rows are made by connecting the positive end of each diode. The negative end 
one diode is connected to the negative end of other diode. For making the columns of this display, 
similarly the 8 columns are made by connecting the negative end of each diode. All these diodes 
are connected with each other through bare copper wire and all these are should be properly sold 
otherwise there would be no connection between all these.

Dot Matrix Interfacing with Microcontroller:
============================================
The dot matrix display consists of rows and columns, in these rows and columns LEDs are connecting. 
These can be on or off as wish, but this can be only done through microcontroller.

Applications of LED Matrix Display:
-----------------------------------
LED matrix display is device used for displaying the information on machine, railway departure 
indicators, clocks and there are so many other devices which required a simple display of very 
low resolution. These displays are available in different resolutions. Here we explain the 
applications of 2-dimensional display used in different devices.

Television Sets
Computer Monitors
Head Mounted Displays
Broadcast Reference Monitors
Medical Monitors.

In this application, driving a 7x5 anode column matrix LED display is examined.In practice, 
A, B, C, D, E, + and bidirectional arrow characters are shown on the matrix LED. Scanning 
method has been applied in practice.In the program, the information of the characters to be 
displayed on the first matrix LED screen is defined as a string.It is calculated on the data 
content in the strings.2 functions are defined in the program.One of them is the column selection 
function and the other is the function to send characters to the matrix LED.There is only one 
function parameter in the column selection function. This is the "s" parameter.Switch-case 
structure is used in the function. When the function is called, the corresponding column is 
activated according to the value of the incoming parameter and the other columns are inactive.
In the function of writing data to the matrix, 2 parameters are used. The first of these 
parameters is for the selection of the character string to be displayed and the other is 
for the display of the characters to be displayed on the matrix LED display.With the 
for(i = 0; i <count; ++ i) command, the function has been scanned up to the value of the 
"count" variable. The other for (k = 0; k <10; ++ k) loop has been scanned.The scanning 
process should be greater than 16 per second.In this cycle, 10 scans have been performed.
Since there are 5 columns in total and each column is scanned for 1 ms, each column has a 
row every 5 ms. (There is a certain delay in the processing of the commands in the program. 
However, this time is not included in the column scanning process because the processing 
time of the commands is very low. For example, in the PIC microcontroller, each command is 
processed in 1 micro second.)When a total of 10 scans are made, a column is scanned every 
5 ms x 10 = 50 ms. If each column is scanned 1 time in 50 ms, it means it is scanned 20 
times per second.This is enough for the human eye to see stagnant, not perceive the on 
and off of the LEDs during scanning.

Column selection operation is performed with the third for(j = 0; j <5; ++ j) loop. 
At the beginning of each loop, the column is selected by calling the colselect() function 
first, and then output_b (ch [j]); With the command, the relevant character information 
is sent to the B port.In the loop, starting from 0, the value of i is incremented by 1 when 
it comes to the beginning of each cycle. Thus, 5 columns are selected in turn and the row 
LEDs that need to be opened in each column are sent to the B port while the relevant column 
is active.The active time of each column is determined as 1 ms. In the main function, the 
function of sending data to the matrix is sent_data_matrix (A, 20); With this command, the 
variable "count" is set to 20 for the duration of the character on the screen.When the scanning 
process in the program was done 10 times, a total of 50 ms time passed. Since each scan will 
be done 20 times, each character stays on the display in 20x50 = 1000 ms, that is, in 1 second.
By changing the value of the "count" variable, the time the character appears on the display 
can be decreased and increased.With the infinite loop, the characters will run sequentially 
on the screen.

The program has proteus drawings. It can be run by inserting the hex code 
of the program into it.

Good work and Best Regards.