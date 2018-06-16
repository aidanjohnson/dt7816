This is a test of the DT78xx Asynchronous IO file operations. This example
configures the board to sample analog input 0,tachometer and measure counter.
The sampled data is read asynchronously from the input stream and written to a
CSV file.

-------------------------------------------------------------------------------
Samples AIN0, measure counter and tachometer channels and writes data
to specified file in CSV format

Usage 

aio-in [options] <file>
Options
-b buffers : number of buffers queued, default 3
-s samples : number of samples per buffer, default 1000
-c clk     : sampling rate in Hz, default is 100KHz
-m         : sample the measure count between tach rising edges
-t         : sample the tachometer
-g {1/10}  : AIN0 gain 1 or 10, default is 1 for +/-10V full scale. This option
			 applies to the DT7837 only, and is ignored in other boards

-------------------------------------------------------------------------------
Test setup 

     +-------------------+                       +-------------------+
     | Signal generator  |                       | DT7837/DT7816     |
     |                   |                       |                   |
     |           wave out+---------->------------+AIN0               |
     |            TTL out+---------->------------+Tach in            |
     |                   |                       |                   |
     +-------------------+                       +-------------------+

Connect a signal generator's waveform output (sine/triangle/ramp/square) to 
AIN0 and optionally the TTL output to the tachometer input of the board. Both
outputs should have the same frequency.

If this example application is run with the -m and -t command line options, the
resultant CSV file will have the analog values in volts and the tachometer and 
measure counters will report the frequency of the TTL signal in Hz.
 
