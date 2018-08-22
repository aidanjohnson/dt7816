## Operation Instructions

1. Assuming the above installation and connection instructions were performed successfully, connect a Linux PC to the DT7816 board via the USB-Serial cable. On the serial end, connect the female header to the J10 pins (the centre row of the parallel row pin trio). Have the black lead attach to pin 1 (the pin closest to the J10 label and microSD card reader. Pair the PC and board with a male-to-male Ethernet cable, as described in the above instructions. Plug the DC power cable to the board so it boots up.

2. In Terminal on the PC, run the command `screen /dev/ttyUSB0 115200` to connect to the serial console of the DAQ. The terminal console will initially be blank; be patient and after a few moments press the 'return' carriage key. Now some boot messages should be displayed. When it asks for a username, type `root` and type `root` for the password. You now are accessing the serial console.

3. To check that the NFS server is functioning, type the command `ls -l /usr/local/dt7816-nfs`. You should then see a list of all the files in the `/opt/ti-sdk-am335x-evm-07.00.00.00/` directory on the PC. 

4. Now that we are confident that the preliminary steps are functioning correctly, we can then access the programs or applications that we've written in C. For our purposes we will be running the `recorder` program such that the board will autonomously sample and record the soundscape. ***—more to be added later on mounting a local storage device (i.e., the [SSD](https://github.com/aidanjohnson/dt7816/issues/10)) at a predefined file structure location—***

5. Inconveniently, the board's local time clock needs to be set and synchronised to a common time so the [`AIFF`](https://en.wikipedia.org/wiki/Audio_Interchange_File_Format) files can be properly time-stamped in their file name. The naming convention follows the [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) standard so time is in UTC (Coordinated Universal Time), also known as GMT (Greenwich Mean Time).  ***—more on a common external clock that is described in the [User Manual](https://github.com/aidanjohnson/dt7816/tree/master/UM7816.pdf) on pp. 35-39 and p. 48 as it is implemented—***

6. Since we want to run the `recorder` program without the PC connected to the board, we will need to copy the program over to local, on-board memory. To do so, run the command `cp -r /usr/local/dt7816-nfs/example-applications/dt78xx-examples/recorder/ /usr/local/`. Then change directories to that location with `cd /usr/local/recorder`.

7. Now we can run the program. To do so, run the command `./release/recorder <identifier> [options]` on the serial console (via Terminal) where `<identifier>` is a identifier of your choosing for the board's recordings (e.g., N for North), and `[options]` is the set of optional command line parameters (note that the board will run with the default values predefined in the source C code). The "help" display describes the options available. It is reproduced below for convenience.
   ```text
   Samples AIN* (where AINx is a combination of AIN0/1/2/3/4/5/6/7 and at most 8
   simultaneous channels) and writes data to timestamped file in AIFF format files 
   saved to a predefined storage path. All options below are not required, only 
   the file identifier is required. The files are saved to 
   <path>/<prefix>_<YYYYMMDD>T<HHmmssuuuuuu>Z.aiff
   
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
   -p|--phi     : latitude (decimal coordinate) of recording site; defaults 47.655083.
                  Northern hemisphere coordinates are positive, and southern negative.
   -l|--lambda  : longitude (decimal coordinate) of recording site defaults -122.293194.
                  Eastern hemisphere coordinates are positive, and western negative.
   ```
   (The decision of naming the flags of the later two options is based on ([geographic coordinate notation](https://en.wikipedia.org/wiki/Geographic_coordinate_system).) If all user input parameters are okay, a console message will appear waiting for the user to start data recording. At the console message, type 's' and then press 'return' key. The program will now automatically run saving the recordings to the local storage directory as `.aiff` files. The console will print information about the written files as it records and saves to the storage directory predefined in the C code `main.c`.

   **Sunrise and Sunset Times**

   Failing to restrain from making a *Fiddler on the Roof* [reference](https://en.wikipedia.org/wiki/Sunrise,_Sunset), ~~the program is fed a `.txt` file coining the sunset times interleaved with the sunrise times of a location determined by its latitude and longitude coordinates. The [US Naval Observatory](http://aa.usno.navy.mil/data/docs/RS_OneDay.php) has a database of these times accessible using a [JSON API](http://aa.usno.navy.mil/data/docs/api.php). The [Jupyter Notebook](http://jupyter.org/index.html) created for process, [`navy_json_sunsight_sunclipse.ipynb`](https://github.com/aidanjohnson/dt7816/tree/master/misc/navy_json_sunsight_sunclipse.ipynb), contains a script that writes the sunset and sunrise times (indicating the time of dusk and dawn) for given range of days to the file [`sunup_sundown.txt`](https://github.com/aidanjohnson/dt7816/tree/master/misc/sunup_sundown.txt) in ISO 8601 format. These dates and times are read by the `recorder` program so that the data sampling and recording only occurs when the bats are out foraging (i.e., at night).~~ the `recorder` program is given a latitude and longitude coordinate pair for the location of the recording site in order to calculate the sunset and sunrise times for each day in the set duration in days. The sampling regime begins immediately after starting through the command line. 

   **Debug LEDs**
   
   The LEDs (LEDx) on the board below the debug pins will light up to indicate whether the channels are being read and recorded (written).
   * 8 LEDs in total.
   * LEDx ON (1) := channel (AINx) is currently reading/writing (R/W) the input.

   **Indicator LED Locations**

   Viewing the DT7816 such that the debug pin row is above the user LEDs, i.e. the DC in, USB, Ethernet, etc. are at the bottom), the LEDs are located and orientated like so:

   |  **PIN1** |  **PIN2** |  **PIN3** |  **PIN4** |  **PIN5** |  **PIN6** |  **PIN7** |  **PIN8** |  **PIN9** | **PIN10** |
   |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
   |           |  **LED7** |  **LED6** |  **LED5** |  **LED4** |  **LED3** |  **LED2** |  **LED1** |  **LED0** |           |

   where each LED is defined by the state (R/W or not R/W) of its respective analog input:
   * LED0 := AIN0
   * LED1 := AIN1
   * LED2 := AIN2
   * LED3 := AIN3
   * LED4 := AIN4
   * LED5 := AIN5
   * LED6 := AIN6
   * LED7 := AIN7

   The analog input channels have the following bit coding returned by `IOCTL_CHAN_MASK_GET`, which enables/disables the LEDs debug indicators (where `0x` indicates a hexadecimal number):
   * AIN0 = 0x01
   * AIN1 = 0x02
   * AIN2 = 0x04
   * AIN3 = 0x08
   * AIN4 = 0x10
   * AIN5 = 0x20
   * AIN6 = 0x40
   * AIN7 = 0x80

   **Analog Inputs Locations**

   For the input header pins (J16), i.e. the right header at the top of the board when viewed from the same perspective as before, is grouped like this where the topmost row is the topmost row of the header:

   |  **2** |  **4** |  **6** |  **8** | **10** | **12** | **14** | **16** | **18** | **20** |
   |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
   |  **1** |  **3** |  **5** |  **7** |  **9** | **11** | **13** | **15** | **17** | **19** |

   The analog inputs (AINs, or AINx) are defined as:
   * PIN5 := AIN0
   * PIN7 := AIN1
   * PIN9 := AIN2
   * PIN11 := AIN3
   * PIN13 := AIN4
   * PIN15 := AIN5
   * PIN17 := AIN6
   * PIN19 := AIN7

   and their corresponding analog grounds (AGRDs, AGRDx) are defined as:
   * PIN6 := AGRD0
   * PIN8 := AGRD1
   * PIN10 := AGRD2
   * PIN12 := AGRD3
   * PIN14 := AGRD4
   * PIN16 := AGRD5
   * PIN18 := AGRD6
   * PIN20 := AGRD7