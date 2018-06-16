This utility calibrates the ADC and DAC in the DT7816. Refer to the DT7816
User's Manual for the calibration procedure

Usage : 
dt7816cal {aout|ain}
Options : Either aout or ain. aout calibrates analog output, ain calibrates 
          analog input  

ADC calibration is based on the average gain and offset of all 8 channels. 
AIN0 through AIN7 must be connected in parallel and then connected to either 
AGND or to the +9V source when directed by the program.
