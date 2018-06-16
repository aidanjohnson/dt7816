This application samples analog input AIN0 at the maximum rate, computes the
spectrum and displays waveforms in a web browser. If this board's IP address
is ip-addr, connect to this application from any web browser using the URL
http://ip-addr:8080  
  
Usage : ./release/sig-analyzer [options]

Options
-r|--docroot <path> : path to directory with all resource files
-d|--daemon         : runs this application as a daemon process
-n|--nowindow       : do not window sampled data before computing FFT. Default, 
                      uses a 4-term Blackman Harris window  
-a|--auto           : auto trigger acquisition. By default, acquisition is 
                      triggered when the voltage on AIN0 crosses 0V rising    
