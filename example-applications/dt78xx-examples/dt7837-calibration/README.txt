dt7837cal is a command line calibration program for the DT7837. It
allows a user to perform three basic tasks:
-1- manually adjust any of the calibration potentiometer on any input channel.
-2- automatically calibrate a channel.
-3- restore all calibration potentiometers to their original factory 
    values.

BASIC INFORMATION
-----------------
There are 32 calibration potentiometers on the DT7837 analog input subsystem.
These are organized as:
4 channels (0 - 3)
2 channel gains (1 and 10)
2 type of pots (offset and gain)
2 sampling rate (low range and high range)

The offset potentiometer is calibrated with 0V on the input (short). 
The gain potentiometer is calibrated with a near-full-scale voltage.
We use 9.375V when the input channel gain is 1 and 0.9375V when
the input channel gain is 10. Each potentiometer value has a range 
of 0 to 255 (8 bits).

Calibration values are also sampling rate frequency dependent. We 
split the DT7837's operating range into two halves - those above 
52734Hz and those equal to or below 52734Hz.

USAGE
-----
	./dt7837cal

Run "dt7837cal" from a command line terminal to start the calibration 
utility. There are no command line options.

The main user interface always shows the current values for the  
32 potentiometer. 

Select the task to perform. You must use the "Enter" key to complete
any input. 

The program will prompt you for input and when necessary, ask you to 
set the voltage source to the channel's input.

