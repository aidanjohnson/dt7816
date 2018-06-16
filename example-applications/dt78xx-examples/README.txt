DT78xx EXAMPLES :
-----------------
This directory has several examples illustrating the functions in the DT78xx
family of boards. Please read the README.txt files in the sub directories
for details of a specific example.

In general, each example (or board application) is an executable that runs in
the board and interfaces with the DT78xx device drivers. The latter implements
virtual device files for a specific function (also referred to as subsystem)
in the board. For example, in the DT7837, the subsystems can be accessed via
the following device files,

/dev/dt7837-ain         : Analog input     
/dev/dt7837-aout        : Analog output     
/dev/dt7837-din         : Digital input   
/dev/dt7837-dout        : Digital output  
/dev/dt7837-measure     : Measure counter    
/dev/dt7837-tach        : Tachometer  
/dev/dt7837-ctr-tmr     : Counter Timer  
/dev/dt7837-stream-in   : Input stream
/dev/dt7837-stream-out  : Output stream

Board applications access and control each subsystem by opening the device
file, issuing IOCTLs to configure, control and access features, read from
and write to the file as applicable. For example, to read the digital inputs,
one would open the /dev/dt7837-din file, read from it to get a snapshot
of the status of the 8 digital input bits and then close the file.

HOW TO BUILD :
--------------
make [debug=1] [RULES_DIR=path1] [DT78xx_DIR=path2] [COMN_DIR=path3] 
			[BOARD_TYPE=DT78xx] {all|clean}

If make is invoked with debug set to 1, the debug version of this application
is built/cleaned/installed. By default, the release version is built.
 
RULES_DIR specifies the path to the Rules.make file installed by the TI SDK.

DT78xx_DIR specifies the path to the DT78XX header files. 

COMN_DIR is the directory where DT78xx examples common files are.

BOARD_TYPE specifies the board type. Specify either DT7837 or DT7816

If either RULES_DIR/DT78xx_DIR/COMN_DIR argument is absent this Makefile uses 
defaults


