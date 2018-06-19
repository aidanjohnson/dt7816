This is a custom application for DT7816 bat array asynchronous I/O sampling
that configures the board's analog input 0, tachometer and measure counter.
The sampled data is read asynchronously from the input stream and written 
to a WAV file. See:
https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
for additional details on (a)synchronous I/O.

-------------------------------------------------------------------------------
Samples AIN0, measure counter and tachometer channels and writes data
to specified file in WAV format

Usage 

bat-array [options] <file>
Options
-b buffers : number of buffers queued, default 3
-s samples : number of samples per buffer, default 1000
-c clk     : sampling rate in Hz, default is 400KHz
-m         : sample the measure count between tach rising edges
-t         : sample the tachometer

-------------------------------------------------------------------------------
Test setup 

     +-------------------+                       +-------------------+
     | Signal generator  |                       | DT7816            |
     |                   |                       |                   |
     |           wave out+---------->------------+AIN0               |
     |            TTL out+---------->------------+Tach in            |
     |                   |                       |                   |
     +-------------------+                       +-------------------+

Connect a signal generator's waveform output (sine/triangle/ramp/square) to 
AIN0 and optionally the TTL output to the tachometer input of the board. Both
outputs should have the same frequency.

If this example application is run with the -m and -t command line options, the
resultant WAV file will have the analog values in volts and the tachometer and 
measure counters will report the frequency of the TTL signal in Hz.
 
