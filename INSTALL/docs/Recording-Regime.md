Given the margin of safety `MoS`, the board will follow this [finite-state machine](https://en.wikipedia.org/wiki/Finite-state_machine), where `Day` is the total number of elapsed days of recording as defined by each sunrise. The `Idle` state corresponds to the board not recording (the off cycle) and the `Record` state corresponds to the board recording each of the selected analog input channels (the on cycle). The [daily duty cycle](https://en.wikipedia.org/wiki/Duty_cycle) (the states) is defined by the current day's calculate sunrise (`Up`) and sunset (`Down`) times, given latitude and longitude coordinates of the recording site, in relation to current time `Time`.

![regime](https://github.com/aidanjohnson/dt7816/blob/master/misc/regime_recorder.png)

### Regime
1. [Connect](https://github.com/aidanjohnson/dt7816/wiki/Connecting:-Operation) the board to the field laptop via USB-Serial and Ethernet once the board has been supplied power, connected to external storage, and positioned (with microphones) where desired. This will be the field user's opportunity to synchronise the local time clock and run the software [`recorder`](https://github.com/aidanjohnson/dt7816/tree/master/example-applications/dt78xx-examples/recorder). The write path to the external storage will need to be entered into the C source code and compiled beforehand. The external drive should have the path `/media/...`.

2. The safety margin is to be specified in the command line when running the program. It can also be pre-defined and compiled beforehand.

3. Depending on the current local time, the board will either enter its idle or recording state. In the recording state the user should see the same number of LEDs flashing on as analog input channels selected. If the board is idling no LEDs should be lit. At this point the board can be left unattended.

4. The board will follow the finite-state machine above.

5. For the 3-day period, the board will continue its duty cycle as specified. If the duration was set via command line when the recording was begun, the program will stop (i.e., return successfully) when complete. Otherwise, the program will need to be manually aborted via the serial console. Setting a recording duration will make the regime truly unattended as the program will stop when complete without user input. The same protocol for the 8 LED row applies, as always. 

6. Each recording file will be written to the path `/media/...` with the naming convention `<ID>_<YYYMMDD>T<HHmmssuuuuuu>Z.aiff`. All of which can be accessed via the SSD M.2 SATA-to-USB adapter on a PC.