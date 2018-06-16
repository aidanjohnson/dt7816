#   ----------------------------------------------------------------------------
#  Makefile to build all examples
#
#  Usage : make [-i] [debug=1] [RULES_DIR=path1] [DT78xx_DIR=path2] [FFTW_DIR=path3]
#          [BOARD_TYPE=DT78xx] {all|clean}

#  -i will ignore build errors and continue building.
#  If make is invoked with debug set to 1, the debug version of all examples
#  are built/cleaned/installed. By default, the release version is built 
#  RULES_DIR specifies the path to the Rules.make file installed by the TI SDK.
#  DT78xx_DIR specifies the path to the DT78XX header files. 
#  FFTW_DIR specifies the path to FFTW header and library files. !!!You must
#   specify this, otherwise some examples will not build. Use the -i option to
#  ignore such errors and build all examples that don't use FFTW libraries.
#  BOARD_TYPE selects the type of board. By default, this makefile sets it to
#  DT7837. You can override that by specifying a different BOARD_TYPE, such as
#  DT7816, in the command line.
#
#  Note that any of the above options can be set in the environment as
#  variables. To use the definition from the environment instead of this
#  makefile, invoke make with the -e (or --environment-overrides) option in 
#  the command line.

all : check_board_type
	make -C ./aio-in
	@echo 
	make -C ./aio-out
	@echo 
	make -C ./aout-single
	@echo 
	make -C ./clk-gen
	@echo 
	make -C ./digio
	@echo 
	make -C ./dt7837-calibration
	@echo 
	make -C ./dt7816-calibration
	@echo 
	make -C ./event-counter
	@echo 
	make -C ./function-gen
	@echo 
	make -C ./fir-filter
	@echo 
	make -i -C ./sig-analyzer
	@echo
	make -i -C ./usb-loopback
	@echo 
	make -C ./web-server
	@echo 
	@echo Built the following
	@find . -executable -type f -exec ls -l {} \+
	
clean:
	make -C ./aio-in clean
	make -C ./aio-out clean
	make -C ./aout-single clean
	make -C ./clk-gen clean
	make -C ./digio clean
	make -C ./dt7837-calibration clean
	make -C ./dt7816-calibration clean
	make -C ./event-counter clean
	make -C ./function-gen clean
	make -C ./fir-filter clean
	make -C ./sig-analyzer clean
	make -C ./usb-loopback clean
	make -C ./web-server clean

check_board_type:
	@test "$(BOARD_TYPE)" != "" || \
	(printf "Please specify BOARD_TYPE as a make parameter \n \
	  make BOARD_TYPE=DT7837\nor as environment variable\n \
	  export BOARD_TYPE=DT7816\n"; exit 1;)
	@echo --------------------------------------
	@echo    Building examples for $(BOARD_TYPE)
	@echo --------------------------------------
