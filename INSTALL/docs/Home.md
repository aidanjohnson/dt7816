## Bat Array: MCC DT7816

This is a custom application for DT7816 autonomous asynchronous I/O sampling that configures the board's analog inputs. The sampled data is read [asynchronously](https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx) from the input stream and written to a AIFF file. The following documentation provides a step-by-step guide to using this software.

See the [manufacturer guide](https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/DT7816_Getting_Started.htm) for the [DT7816](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) if you want a more thorough guide necessary for manual setup and building. This repository is intended to make the building process easier and faster by automating it through a script. Download the tarball in [`INSTALL`](https://github.com/aidanjohnson/dt7816/tree/master/INSTALL) to build all the code for this DAQ, which is installed to the directory: `/opt/ti-sdk-am335x-evm-07.00.00.00/`. Note that your directory will not contain the directories `INSTALL` and [`misc`](https://github.com/aidanjohnson/dt7816/blob/master/misc); these have been only included for convenience. Follow the instructions below to build it all from scratch.

### Acknowledgements
Thank you to the [Applied Physics Laboratory](http://www.apl.washington.edu/) at the University of Washington and the [UW Institute for Neuroengineering](http://uwin.washington.edu/) for funding and support, and to the [Union Bay Natural Area](https://botanicgardens.uw.edu/center-for-urban-horticulture/visit/union-bay-natural-area/) for support. This project was funded by the UW Institute for Neuroengineering and the Washington Research Foundation Funds for Innovation in Neuroengineering and the Air Force Center of Excellence on Nature-Inspired Flight Technologies and Ideas ([NIFTI](http://nifti.washington.edu/)). Contact: [Wu-Jung Lee](https://leewujung.github.io/) at wjlee@apl.washington.edu and [Aidan Johnson](https://aidanjohnson.github.io/) at johnsj96@uw.edu.

This project (licensed by [GPLv3](https://opensource.org/licenses/GPL-3.0)) uses the open source libraries:
* [LibAiff](http://aifftools.sourceforge.net/libaiff/) by Marco Trillo ([MIT License](https://opensource.org/licenses/mit-license.php))
* [ArduinoRingBuffer](https://github.com/wizard97/ArduinoRingBuffer) by Aaron Wisner ([MIT License](https://opensource.org/licenses/MIT))
* [DT78xx software](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) by Data Translation Inc ([GPLv2](https://opensource.org/licenses/gpl-2.0.php))
* [Free C source for computing sunrise/set times](http://stjarnhimlen.se/english.html) by Paul Schlyter ([Public Domain](http://stjarnhimlen.se/snippets/snippets.(c)))
