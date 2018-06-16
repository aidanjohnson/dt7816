This application is an embedded web server using the DT7837. From a host's 
browser the digital input/output, counter/timer, measure counter, tachometer,
analog inputs, sampling rate, trigger sources, buffer parameters can be 
configured. Acquisition can be controlled and the results can be downloaded as
a csv file to the host.

This example uses the following open source libraries/code
1) mongoose web server  http://cesanta.com/. 

==================================================================
IMPORTANT NOTE ABOUT LIBMONGOOSE 

Details of libmongoose, including its embedding guide and API reference are at
http://cesanta.com/libmongoose.shtml

libmongoose is an alternative to using Apache2 and is easier to configure, embed
and has a smaller footprint.

Licensing information  http://cesanta.com/license.shtml 

This software is distributed under commercial and GPLv2 licenses.
The GPLv2 open source license does not generally permit incorporating this
software into non-open source programs. For those customers who do not wish to
comply with the GPL open source license requirements, CESANTA offers a full
commercial license without any of the GPL restrictions. Read the Licensing
section and contact us for details about the commercial license and support
options. 

==================================================================
IMPORTANT NOTE ABOUT INSTALLATION
The web server executable and the required resource files, by default, should
be organized as follows in the target DT78xx, under some directory. The web 
server generates dynamic web pages for URLs that don't have a corresponding 
static resource file

~some-directory\webserver-executable
~some-directory\res\*.html			  
~some-directory\res\*.css
~some-directory\res\*.png

==================================================================
EXECUTING THE WEB SERVER

./webserver [options]

Options : Each can either be one letter or the longer string shown below.
-p|--port <number>  : selects HTTP port, default is 8080
-v|--verbose        : enables printf messages
-r|--docroot <path> : path to directory with all resource files
-d|--daemon         : runs this application as a daemon process

==================================================================
TERMINATING THE WEB SERVER
a) If the application is a foreground process type control-C
b) If the application is a daemon, kill it using its PID

==================================================================
CONNECTING TO THE WEB SERVER
The server uses HTTP port 8080 by default. The default can be overridden using
command line options as noted above. 
Therefore, to connect from any browser you must append the port number to the 
IP address of the DT78xx. For example, http://1.1.1.1:8080

