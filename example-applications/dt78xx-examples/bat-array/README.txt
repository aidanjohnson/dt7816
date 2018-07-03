This is a custom application for DT7816 bat array asynchronous I/O sampling
that configures the board's analog inputs. The sampled data is read 
asynchronously from the input stream and written to a AIFF file. See:
https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx
for additional details on (a)synchronous I/O.

-------------------------------------------------------------------------------
Samples AIN* (where AIN* is a combination of AIN0/1/2/3/4/5/6/7 and at most 8
simultaneous channels) and writes data to timestamped file in AIFF format files 
saved to a predefined storage path. All options below are not required, only 
the file identifier is required. The files are saved to 
<path>/<prefix>_<YYYY-DD-MMTHHmmssuuuuuuZ>.aiff

"Usage        : %s <identifier prefix> [options] \n"
"Options\n"
   
"\n"

Usage 

./release/bat-array <identifier prefix> [options]

Required     : a file or location identifier prefix, such as NORTH or 1.\n" 

Options
-i|--inputs  : 8-bit binary string to enable and disable analog input channels
               A channel is on if its bit is 1 and off if its bit is 0. Bit
              positions 0/1/2/3/4/5/6/7 correspond to channels AIN0/1/2/3/4/5/6/7.
               For example, 10101001 enables AIN0/2/4/7 and disables AIN1/3/5/6.
               By default, on channels AIN0 is enabled (i.e., 10000000).  
-s|--samples : number of samples per channel, default SAMPLES_PER_CHAN.
               Note that you are limited to 2^(16-bits) = 65536 samples >=
               (samples per channel)(channels per buffer)(buffers)
-c|--clk     : sampling rate in Hz, default SAMPLE_RATE_HZ.
-b|--buffers : number of buffers per file written, default NUM_BUFFS.
-d|--daemon  : runs this application as a daemon process.
-t|--trig    : when the voltage on either AIN crosses TRIG_LEVEL_V V rising 
               (threshold) acquisition is triggered. By default, acquisition
               is triggered when you start the analog input operation using 
               the ioct.

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
 
