This is a custom application for DT7816 bat array asynchronous I/O sampling
that configures the board's analog input 0. The sampled data is read 
asynchronously from the input stream and written to a WAV file. See:
https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
for additional details on (a)synchronous I/O.

-------------------------------------------------------------------------------
Samples AIN0 and writes data to specified file in WAV format

Usage 

bat-array [options] <file>
Options
-b buffers : number of buffers queued, default 2
-s samples : number of samples per buffer, default 1024
-c clk     : sampling rate in Hz, default is 400KHz

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
 
