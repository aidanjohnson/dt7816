This is a simple test of the digital input and output in the DT78xx family. 
This example writes the value specified in the command line to the digital 
output device file /dev/dt78xx-dout and reads back from the digital input file
/dev/dt78xx-din. It also writes the lower 8 bits of the data to the debug LEDs.
Note that the xx must be substituted with the specific board model, for example,
37 for the DT7837 and 16 for DT7816

The digital outputs may be connected to the digital inputs to  verify that
the value written is read back.

Usage :
--------
./dig-io [hex-value]
Read digital input and optionally write digital out
hex-value, if specified, is written to the digital output
