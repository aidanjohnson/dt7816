#!/usr/bin/env python3
from subprocess import call
import os

path_examples = "/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples"
fftw_path = "/opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/fftw-3.3.4"
dirs = ['aio-in', 'aio-out', 'aout-single', 'clk-gen', 'digio', 'dt7816-calibration', 'event-counter', 'fir-filter', 'function-gen', 'sig-analyzer', 'usb-loopback', 'web-server']
os.chdir(path_examples)
for filename in os.listdir(path_examples):
	if filename in dirs:
		call(["cp", "-r", "/opt/ti-sdk-am335x-evm-07.00.00.00/nbproject", filename])
		os.chdir(filename)
		call(["make", "BOARD_TYPE=DT7816", "clean"])
		call(["make", "BOARD_TYPE=DT7816"])
		if filename == 'sig-analyzer':
			call(["make", "FFTW_DIR="+fftw_path])
		os.chdir("nbproject")
		line = "6c" + "<name>" + filename + "</name>"
		call(["sed", "-i", line, "project.xml"])
		os.chdir("../..")
