 
evt-counter :
--------
This is a simple test of counter timer in the DT78xx family. The example
opens file /dev/dt78xx-ctr-tmr, sends ioctls to configure the counter
timer to count events and reads the counter.
Command line arguments configure the clock and gate source, the digital
input pins used for external clock and gate 

Usage : evt-counter [options]
Options :
-x|--xclk selects external clock, default is internal 48MHz
-g|--gate lo|hi|no : selects external gate lo, external gate hi or no gate
-i|--gatein <number> selects DIN used as external gate, number is 0-7
-c|--clkin <number> selects DIN used as external clock input, number is 0-7
