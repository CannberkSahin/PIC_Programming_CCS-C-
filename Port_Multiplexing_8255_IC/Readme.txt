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

Intel 8255 Integrated Circuit
=============================
The Intel 8255 (or i8255) Programmable Peripheral Interface (PPI) chip was 
developed and manufactured by Intel in the first half of the 1970s for the 
Intel 8080 microprocessor. The 8255 provides 24 parallel input/output lines 
with a variety of programmable operating modes.
The 8255 is a member of the MCS-85 Family of chips, designed by Intel for 
use with their 8085 and 8086 microprocessors and their descendants.It 
was first available in a 40-pin DIP and later a 44-pin PLCC packages. It found 
wide applicability in digital processing systems and was later cloned by other 
manufacturers. The 82C55 is a CMOS version for higher speed and lower current 
consumption.
The functionality of the 8255 is now mostly embedded in larger VLSI processing 
chips as a sub-function. A CMOS version of the 8255 is still being made by 
Renesas but mostly used to expand the I/O of microcontrollers.

Function
--------
The 8255 gives a CPU or digital system access to programmable parallel I/O. 
The 8255 has 24 input/output pins.These are divided into three 8-bit ports 
(A, B, C). Port A and port B can be used as 8-bit input/output ports. Port C 
can be used as an 8-bit input/output port or as two 4-bit input/output ports 
or to produce handshake signals for ports A and B.

The three ports are further grouped as follows:

Group A consisting of port A and upper part of port C.
Group B consisting of port B and lower part of port C.
Eight data lines (D0–D7) are available (with an 8-bit data buffer) to read/write 
data into the ports or control register under the status of the RD (pin 5) and 
WR (pin 36), which are active-low signals for read and write operations respectively. 
Address lines A1 and A0 allow to access a data register for each port or a control 
register, as listed below:

-------------------------------
A1	A0	Port selected
-------------------------------
0	0	port A
--------------------------------
0	1	port B
--------------------------------
1	0	port C
--------------------------------
1	1	control register
--------------------------------

The control signal chip select CS (pin 6) is used to enable the 8255 chip. It is 
an active-low signal, i.e., when CS = 0, the 8255 is enabled. The RESET input 
(pin 35) is connected to the RESET line of system like 8085, 8086, etc., so that 
when the system is reset, all the ports are initialized as input lines. This is 
done to prevent 8255 and/or any peripheral connected to it from being destroyed 
due to mismatch of port direction settings. As an example, consider an input 
device connected to 8255 at port A. If from the previous operation, port A is 
initialized as an output port and if 8255 is not reset before using the current 
configuration, then there is a possibility of damage of either the input device 
connected or 8255 or both, since both 8255 and the device connected will be sending 
out data.
The control register (or the control logic, or the command word register) is an 
8-bit register used to select the modes of operation and input/output designation 
of the ports.

Operational modes of 8255
=========================
There are two basic operational modes of 8255:

Bit Set/Reset mode (BSR mode).
Input/Output mode (I/O mode).
The two modes are selected on the basis of the value present at the D7 bit of the 
control word register. When D7 = 1, 8255 operates in I/O mode, and when D7 = 0, 
it operates in the BSR mode.

Bit Set/Reset (BSR) mode
========================
The Bit Set/Reset (BSR) mode is available on port C only. Each line of port C 
(PC7 - PC0) can be set or reset by writing a suitable value to the control word 
register. BSR mode and I/O mode are independent and selection of BSR mode does not 
affect the operation of other ports in I/O mode:

D7 bit is always 0 for BSR mode.
Bits D6, D5 and D4 are don't care bits.
Bits D3, D2 and D1 are used to select the pin of Port C.
Bit D0 is used to set/reset the selected pin of Port C.

Selection of port C pin is determined as follows:
=================================================
D3	D2	D1	Bit/pin of port C selected
--------------------------------------------------
0	0	0	PC0
--------------------------------------------------
0	0	1	PC1
--------------------------------------------------
0	1	0	PC2
--------------------------------------------------
0	1	1	PC3
--------------------------------------------------
1	0	0	PC4
--------------------------------------------------
1	0	1	PC5
--------------------------------------------------
1	1	0	PC6
--------------------------------------------------
1	1	1	PC7
--------------------------------------------------

As an example, if it is needed that PC5 be set, then in the control word,

Since it is BSR mode, D7 = '0'.
Since D4, D5, D6 are not used, assume them to be '0'.
PC5 has to be selected, hence, D3 = '1', D2 = '0', D1 = '1'.
PC5 has to be set, hence, D0 = '1'.
Thus, as per the above values, 0B (Hex) will be loaded into the Control Word Register (CWR).
-----------------------------------------------------------
D7	D6	D5	D4	D3	D2	D1	D0
-----------------------------------------------------------
0	0	0	0	1	0	1	1
-----------------------------------------------------------

Input/Output mode
=================
This mode is selected when D7 bit of the Control Word Register is 1. There are three I/O modes:

Mode 0 - Simple I/O
Mode 1 - Strobed I/O
Mode 2 - Strobed Bi-directional I/O

Control Word format
===================
D0, D1, D3, D4 are assigned for port C lower, port B, port C upper and port A respectively. 
When these bits are 1, the corresponding port acts as an input port. For e.g., if D0 = D4 = 1, 
then lower port C and port A act as input ports. If these bits are 0, then the corresponding 
port acts as an output port. For e.g., if D1 = D3 = 0, then port B and upper port C act as 
output ports.D2 is used for mode selection of Group B (port B and lower port C). When D2 = 0, 
mode 0 is selected and when D2 = 1, mode 1 is selected.D5 & D6 are used for mode selection of 
Group A ( port A and upper port C). The selection is done as follows:

D6	D5	Mode
--------------------
0	0	0
--------------------
0	1	1
--------------------
1	X	2
--------------------

As it is I/O mode, D7 = 1.
or example, if port B and upper port C have to be initialized as input ports and 
lower port C and port A as output ports (all in mode 0):

Since it is an I/O mode, D7 = 1.
Mode selection bits, D2, D5, D6 are all 0 for mode 0 operation.
Port B and upper port C should operate as Input ports, hence, D1 = D3 = 1.
Port A and lower port C should operate as Output ports, hence, D4 = D0 = 0.
Hence, for the desired operation, the control word register will have to be loaded 
with "10001010" = 8A (hex).

Mode 0 - simple I/O
===================
In this mode, the ports can be used for simple I/O operations without handshaking 
signals. Port A, port B provide simple I/O operation. The two halves of port C can 
be either used together as an additional 8-bit port, or they can be used as individual 
4-bit ports. Since the two halves of port C are independent, they may be used such that 
one-half is initialized as an input port while the other half is initialized as an output port.

The input/output features in mode 0 are as follows:

Output ports are latched.
Input ports are buffered, not latched.
Ports do not have handshake or interrupt capability.
With 4 ports, 16 different combinations of I/O are possible.
'Latched' means the bits are put into a storage register (array of flip-flops) which holds 
its output constant even if the inputs change after being latched.

The 8255's outputs are latched to hold the last data written to them. This is required because 
the data only stays on the bus for one cycle. So, without latching, the outputs would become 
invalid as soon as the write cycle finishes.

The inputs are not latched because the CPU only has to read their current values, then store 
the data in a CPU register or memory if it needs to be referenced at a later time. If an input 
changes while the port is being read then the result may be indeterminate.

Mode 0 – input mode
===================
In the input mode, the 8255 gets data from the external peripheral ports and the CPU reads 
the received data via its data bus.
The CPU first selects the 8255 chip by making CS low. Then it selects the desired port using 
A0 and A1 lines.
The CPU then issues an RD signal to read the data from the external peripheral device via 
the system data bus.

Mode 0 - output mode
====================
In the output mode, the CPU sends data to 8255 via system data bus and then the external 
peripheral ports receive this data via 8255 port.
CPU first selects the 8255 chip by making {\displaystyle {\neg }}{\neg }CS low. It then 
selects the desired port using A0 and A1 lines.
CPU then issues a WR signal to write data to the selected port via the system data bus. 
This data is then received by the external peripheral device connected to the selected port.

Mode 1 - Strobed Input/output mode
==================================
When we wish to use port A or port B for handshake (strobed) input or output operation, 
we initialise that port in mode 1 (port A and port B can be initialised to operate in different modes, 
i.e., for e.g., port A can operate in mode 0 and port B in mode 1). Some of the pins of port C function 
as handshake lines.
For port B in this mode (irrespective of whether is acting as an input port or output port), 
PC0, PC1 and PC2 pins function as handshake lines.
If port A is initialised as mode 1 input port, then, PC3, PC4 and PC5 function as handshake signals. 
Pins PC6 and PC7 are available for use as input/output lines.
The mode 1 which supports handshaking has following features:

Two ports i.e. port A and B can be used as 8-bit i/o ports.
Each port uses three lines of port c as handshake signal and remaining two signals can be used as i/o ports.
Interrupt logic is supported.
Input and Output data are latched.

Input Handshaking signals
=========================
1. IBF (Input Buffer Full) - It is an output indicating that the input latch contains information.
2. STB (Strobed Input) - The strobe input loads data into the port latch, which holds the information 
until it is input to the microprocessor via the IN instruction.
3. INTR (Interrupt request) - It is an output that requests an interrupt. The INTR pin becomes a logic 1 
when the STB input returns to a logic 1, and is cleared when the data are input from the port by the 
microprocessor.
4. INTE (Interrupt enable) - It is neither an input nor an output; it is an internal bit programmed 
via the port PC4(port A) or PC2(port B) bit position.

Output Handshaking signals
==========================
1. OBF (Output Buffer Full) - It is an output that goes low whenever data are output(OUT) to the 
port A or port B latch. This signal is set to a logic 1 whenever the ACK pulse returns from the 
external device.
2. ACK (Acknowledge)-It causes the OBF pin to return to a logic 1 level. The ACK signal is a response 
from an external device, indicating that it has received the data from the 82C55A port.
3. INTR (Interrupt request) - It is a signal that often interrupts the microprocessor when the external 
device receives the data via the signal. this pin is qualified by the internal INTE(interrupt enable) bit.
4. INTE (Interrupt enable) - It is neither an input nor an output; it is an internal bit programmed 
to enable or disable the INTR pin. The INTE A bit is programmed using the PC6 bit and INTE B is 
programmed using the PC2 bit.

Mode 2 - Strobed Bidirectional Input/Output mode
================================================
Only port A can be initialized in this mode. Port A can be used for bidirectional handshake data transfer. 
This means that data can be input or output on the same eight lines (PA0 - PA7). Pins PC3 - PC7 are used 
as handshake lines for port A. The remaining pins of port C (PC0 - PC2) can be used as input/output lines 
if group B is initialized in mode 0 or as handshaking for port B if group B is initialized in mode 1. In 
this mode, the 8255 may be used to extend the system bus to a slave microprocessor or to transfer data 
bytes to and from a floppy disk controller. Acknowledgement and handshaking signals are provided to maintain 
proper data flow and synchronisation between the data transmitter and receiver.


Although the 8255 IC has a more complex structure, it offers a stronger control.
In this application, entry / exit control application has been made with 8255.
Thus, the operation of the 8255 IC can be understood better. In practice, the C 
port of 8255 is set as the inlet and the aport as the exit.Switches are connected 
to the C port. Normally all LEDs connected to the A port are on when the switches 
are open. Whichever switch is turned off, that numbered LED will turn off.
#Use fast_io (port name) command, which is used in other programs in the general 
definition and setting part of the program, is not used in this program.When this 
command was used, it was necessary to specify which port will be used as input and 
output port in the program.If any of the #use xxx_io() commands are not used in 
the program, there is no need to set port port input / output in the program.The 
command #use standard_io() is used in this program. This means that the port 
specified by this command will be set automatically by the compiler program.For 
example, if the input_a() command is used in the program, the compiler sets port 
A as input, and if the output_a() command is used, the compiler sets port A as 
output.If no #use xxx_io() is used in the program, the compiler automatically 
assumes that the #use standard_io() command is used by default.
In the program, two functions are defined for writing and reading to the desired 
port or control recorder on the 8255 IC. For 8255 write operation, the function 
named void _8255_write(char x, char info) has been defined to read the function 
named int _8255_read(char x). Switch-case loop structure is used in 8255 read 
and write functions. Since the write function has no return value, the return 
value is determined as void. The function has 2 parameters. Both parameters are 
of the cahar type.When the write function is called, the switch-case loop branches 
according to the character value of the first variable.For example, 
if _8255_write('r', 0x23) is written when calling the function, the value of x will 
be 'r' and the function will process the commands in the case 'r': part and break; 
will exit the loop with command.It will not handle other case situations. If you 
pay attention to the circuit diagram, the control pins (CD, WR, A0, A1) are connected 
to the A port of PIC16F877.For writing operation, RD pin (pin_a0) logic-1 WR pin (pin_a1) 
pin must be logic-0. The values of pins A0 and A1 must be different values for writing 
to the recorder A, B and C ports.These values according to the desired state 
output_a(0bxxxxxxxx) It is sent to port A with commands. Then output_b (info); The 
second parameter value, which is written when the function is called with the commands, 
is sent to the B port, that is, to the D0-D7 pins of 8255. Thus, 8255 writing functions 
were created.

The 8255 reading function, on the other hand, has a single parameter, the variable whose 
return value is int, which is an integer. Switch-case structure is used in the reading 
function.In the read function, as in the write function, the control bits are initially 
programmed according to the reading status. Then return input_b (); With the commands, 
the function returns with the value read. For example, when the function in the form of 
_8255_read('b') is called in the program, the reading function will go to the case 'b' 
part and set the control pins to read the B port. Then it will return with the value 
read by reading the B port. 

In the main function _8255_write('r', 0b10001001); The control word is written to the 
control register to set the A and B ports as output and C port as input in Mode 0.
Then in the created endless loop data = _8255_read ('c'); The C port inputs of 8255 
are read with the command and the read value is written to the A port of 8255, the value 
of the global variable named 'data'.

The program has proteus drawings. It can be run by inserting the hex code 
of the program into it.

Good work and Best Regards.