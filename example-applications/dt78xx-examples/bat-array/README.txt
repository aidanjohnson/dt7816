This application samples analog input AIN0 at the maximum rate, computes and locally stores the
spectrum.
  
Usage : ./release/bat-array [options]

Options
-r|--docroot <path> : path to directory with all resource files
-d|--daemon         : runs this application as a daemon process
-n|--nowindow       : do not window sampled data before computing FFT. Default, 
                      uses a 4-term Blackman Harris window  
-a|--auto           : auto trigger acquisition. By default, acquisition is 
                      triggered when the voltage on AIN0 crosses 0V rising    
