This is a custom application for DT7816 bat array asynchronous I/O sampling
that configures the board's analog input 0. The sampled data is read 
asynchronously from the input stream and written to a WAV file. See:
https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
for additional details on (a)synchronous I/O.

-------------------------------------------------------------------------------
Samples AIN0 and writes data to specified file in WAV format files saved to a
specified storage path. All options below are not required.

Usage 

bat-array [options] <file or location identifier>
Options
-s|--samples : number of samples per buffer, default 1024
-c|--clk     : sampling rate in Hz, default is 400KHz
-d|--daemon  : runs this application as a daemon process
-t|--trig    : when the voltage on AIN0 crosses 0V rising (threshold) 
               acquisition is triggered. By default, acquisition is triggered  
               when you start the analog input operation using the ioct

-------------------------------------------------------------------------------
Test setup 

     +-------------------+                       +-------------------+
     | Signal generator  |                       | DT7816            |
     |                   |                       |                   |
     |           wave out+---------->------------+AIN0               |
     |                   |                       |                   |
     |                   |                       |                   |
     +-------------------+                       +-------------------+

Connect a signal generator's waveform output (sine/triangle/ramp/square) to 
AIN0.

If this example application is run with no command line options, the resultant 
WAV file will have the analog values in volts.
 
