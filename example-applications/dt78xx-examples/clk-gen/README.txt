 
clkgen :
--------
This is a simple test of counter timer in the DT78xx family. The example
opens file /dev/dt7837-ctr-tmr (or /dev/dt7816-ctr-tmr) and sends ioctls to 
configure the counter timer to generate an output clock from dividing either
the internal clock or an external clock.
Command line arguments configure the clock and gate source, the digital
input pins used for external clock and gate and the digital output pin used
to output the generated clock

Usage : clkgen [options] -p|--period <number> -u|--pulse <number>

-p|--period <number> specifies output clock total period; number is 32-bit
-u|--pulse <number> specifies output clock active period, number is 32-bit
     duty-cyle=(pulse/period); hence pulse must be less than period

Options :
-x|--xclk selects external clock, default is internal 48MHz
-g|--gate lo|hi|no : selects external gate lo, external gate hi or no gate
-i|--gatein <number> selects DIN used as external gate, number is 0-7
-c|--clkin <number> selects DIN used as external clock input, number is 0-7
-o|--clkout <number> selects DOUT used as clock output, number is 0-7
