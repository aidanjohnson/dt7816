 Function generator example :

 This example shows the use of the output stream to output data continuously,
 and how to configure the analog output and output stream. The example uses
 Asynchronous IO (AIO) to generate sine/triangle/sawtooth/square waveform with 
 programmable frequency and amplitude using Direct Digital Synthesis (DDS).
 Digital output 0 generates a pulse waveform with 50% duty cycle, outputs 
 1,2,3 each generate phase shifted pulse waveforms with 25% duty cycle.
-------------------------------------------------------------------------------
Usage :

funcgen [options] {sin|tri|saw|square}

Generate sine/triangle/sawtooth/square waveform with programmable frequency and
amplitude using Direct Digital Synthesis (DDS).
Digital output 0 generates a pulse waveform with 50% duty cycle, 
outputs 1,2,3,4 each generate phase shifted pulse waveforms with 25% duty cycle.

Options : 
-c|--clk    : Frequency of generated waveform, default 1KHz
-n|--numbuf : Number of buffers queued, default 8
-s|--samples: Number of *samplesper buffer, default 1024
-v|--volt   : Peak-to-peak output voltage, default 1V
