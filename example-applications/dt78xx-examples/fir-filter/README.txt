FIR filter example :

This example shows the use of the output stream and input stream used
simultaneously and continuously. AIN0 is configured and sampled at the
specified clock rate, the sampled buffers are FIR filtered using either
coefficients from a user specified file or defaults for a low-pass filter,
and the resultant output to AOUT0 at the specified clock rate.

-------------------------------------------------------------------------------
Usage :

firfilt [options] [coeff-file]

Sample AIN0, filter acquired buffers and output to AOUT0. FIR filter  
coefficients read from optional coeff-file or default to 6KHz low-pass filter
Options : 
-c|--clk    : Sampling rate in Hz, default 100000
-n|--numbuf : Number of buffers queued, default 8
-s|--samples: Number of *samples* per buffer, default 1024

If coeff-file is specified, each line must have a single coefficient in 
single precision floating point format. See the examples files.
