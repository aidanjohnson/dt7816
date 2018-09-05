# Warning
The code in this (master) branch is _pre-alpha_ grade, not alpha, beta, or gamma (release candidate) grade. Please check in on as development progresses. Two _major_ issues include:
1. Unpractically small recording file time duration.
2. Buffered recording that does not take advantage of asynchronous I/O, resulting in time gaps between buffered recording portions.

The branch https://github.com/aidanjohnson/dt7816/tree/double-buffer-dev is under development is _alpha_ grade, and soon to be beta grade. It addresses both above issues (1. has been resolved and 2. is in progress). Contact Aidan Johnson for enquiries (see below).

# Documentation
The following documentation is essential for using this autonomous recorder program for the [MCC DT7816](https://www.mccdaq.com/Products/ARM-DAQ/DT7816). This program has the specific purpose of serving as an acoustic sampling array for studying the neural computational principles behind biosonar (i.e., navigation and coordination of foraging bats). The Wiki is the most complete and up-to-date guide, while the Doxygen documentation is supplementary. 
* [Wiki](https://github.com/aidanjohnson/dt7816/wiki)
* [Doxygen](https://github.com/aidanjohnson/dt7816/tree/f8a4ccb92a67c16e4d23e182c011c55ef94b3e6c/example-applications/dt78xx-examples/recorder/Documentation/html)

## Acknowledgements
Thank you to the [Applied Physics Laboratory](http://www.apl.washington.edu/) at the University of Washington and the [UW Institute for Neuroengineering](http://uwin.washington.edu/) for funding and support, and to the [Union Bay Natural Area](https://botanicgardens.uw.edu/center-for-urban-horticulture/visit/union-bay-natural-area/) for support. This project was funded by the UW Institute for Neuroengineering and the Washington Research Foundation Funds for Innovation in Neuroengineering and the Air Force Center of Excellence on Nature-Inspired Flight Technologies and Ideas ([NIFTI](http://nifti.washington.edu/)). Contact: [Wu-Jung Lee](https://leewujung.github.io/) at wjlee@apl.washington.edu and [Aidan Johnson](https://aidanjohnson.github.io/) at johnsj96@uw.edu.

This project uses the open source libraries:
* [LibAiff](http://aifftools.sourceforge.net/libaiff/) by Marco Trillo ([MIT License](https://opensource.org/licenses/mit-license.php))
* [ArduinoRingBuffer](https://github.com/wizard97/ArduinoRingBuffer) by Aaron Wisner ([MIT License](https://opensource.org/licenses/MIT))
* [DT78xx software](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) by Data Translation Inc ([GPLv2](https://opensource.org/licenses/gpl-2.0.php))
* [Free C source for computing sunrise/set times](http://stjarnhimlen.se/english.html) by Paul Schlyter ([Public Domain](http://stjarnhimlen.se/snippets/snippets.(c)))
