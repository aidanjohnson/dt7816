This is a custom application for DT7816 bat array asynchronous I/O sampling
that configures the board's analog inputs. The sampled data is read 
asynchronously from the input stream and written to a AIFF file. See:
https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
for additional details on (a)synchronous I/O.

-------------------------------------------------------------------------------
Samples AIN* (where AINx is a combination of AIN0/1/2/3/4/5/6/7 and at most 8
simultaneous channels) and writes data to timestamped file in AIFF format files 
saved to a predefined storage path. All options below are not required, only 
the file identifier is required. The files are saved to 
<path>/<prefix>_<YYYY-DD-MMTHHmmssuuuuuuZ>.aiff

Usage        : ./release/recorder <identifier prefix> [options]

Required     : a file or location identifier prefix, such as NORTH or 1.

Options
-i|--inputs  : 8-bit binary string to enable and disable analog input channels
               A channel is on if its bit is 1 and off if its bit is 0. Bit
               positions 0/1/2/3/4/5/6/7 correspond to channels AIN0/1/2/3/4/5/6/7.
               For example, 10101001 enables AIN0/2/4/7 and disables AIN1/3/5/6.
               By default, only channel AIN0 is enabled (i.e., 10000000).  
-s|--samples : number of samples per channel; defaults 65536.
               Note that you are limited to 2^(16-bits) = 65536 samples >=
               (samples per channel)(channels per buffer)(buffers)
-c|--clk     : sampling rate in Hz; defaults 400000 Hz.
-b|--buffers : number of buffers per file written, defaults 1.
-d|--dur     : fixed duration of sampling period in days at night as determined
               by sunset and sunrise times; defaults 7 days.
-t|--trig    : when the voltage on either AIN crosses 0.0 V rising 
               (threshold) acquisition is triggered. By default, acquisition
               is triggered when you start the analog input operation using 
               the ioct.
-m|--margin  : margin of safety before the time of sunset and after the time of
               sunrise in seconds (hours*3600); defaults 3600 s. 
-n|--night   : night cycling (on after sun down and off after sun up). Sun up and
               down times calculated. Defaults to disabled state (recording 24
               hours a day).
               
-------------------------------------------------------------------------------
Test setup 

     +-------------------+                       +-------------------+
     | Signal generator  |                       | DT7816            |
     |                   |                       |                   |
     |           wave out+---------->------------+AIN*               |
     |                   |                       |                   |
     |                   |                       |                   |
     +-------------------+                       +-------------------+

Connect a signal generator's waveform output (sine/triangle/ramp/square) to 
AIN*.

If this example application is run with no command line options, the resultant 
AIFF file will have the analog values quantised and digitised in volts.
 
