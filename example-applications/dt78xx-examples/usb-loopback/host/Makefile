#   ----------------------------------------------------------------------------
#  Makefile to build a USB application that runs in the host PC and
#  communicates with a corresponding application executing in the DT78xx board.
#  The two applications communicate over USB pipes sending and receiving data.
#
#  PREREQUISITES :
#  The program requires libusb. libusb is a C library that gives applications
#  easy access to USB devices on many different operating systems. libusb is
#  an open source project, the code is licensed under the ​GNU Lesser General
#  Public License version 2.1 or later. If libusb is not already installed, 
#  please see http://www.libusb.org/ to download and install libusb.
#
#  In this makefile LIBUSB_INCDIR must be edited to refer to the directory that
#  has libusb header files; LIBUSB_LIBDIR must refer to the directory where
#  libusb-1.0.so is present. In addition, specify the environment variable
#  LD_LIBRARY_PATH to point to the directory path containing the shared
#  library, libusb-1.0.so. This will specify to the run time loader that the
#  library paths will be used during execution to resolve dependencies. 
#
#  USAGE :
#	make [debug=1] {all|clean}
#
#  If make is invoked with debug set to 1, the debug version of this application
#  is built/cleaned/installed. By default, the release version is built 
#
#   ----------------------------------------------------------------------------
#   Included defined variables
#   ----------------------------------------------------------------------------

#   ----------------------------------------------------------------------------
#   Variables passed in externally
#   ----------------------------------------------------------------------------
CFLAGS ?=

#   ----------------------------------------------------------------------------
#   Linux compiler defaults to gcc for the host OS
#   ----------------------------------------------------------------------------
CC := gcc

#   ----------------------------------------------------------------------------
#   General options, sources and libraries
#   ----------------------------------------------------------------------------
NAME := host-usb-loopback
SRCS := main.c xcrc32.c 
HDRS := 
OBJS :=
DEBUG :=
BIN := host-usb-loopback
LIBUSB_INCDIR = /usr/local/include/libusb-1.0	
LIBUSB_LIBDIR = /usr/local/lib	
LIBS := $(LIBS) -lpthread -lusb-1.0

#   ----------------------------------------------------------------------------
#   Compiler and Linker flags 
#   ----------------------------------------------------------------------------
EXTRA_FLAGS := -std=gnu99
ifeq (${debug}, 1)
OBJDIR := debug
EXTRA_FLAGS += -g3 -Wall
else
OBJDIR := release
EXTRA_FLAGS += -O3
endif

OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

#   ----------------------------------------------------------------------------
#   Compiler include directories 
#   ----------------------------------------------------------------------------
INCLUDES := -I../ -I$(LIBUSB_INCDIR)

#   ----------------------------------------------------------------------------
#   Compiler symbol definitions 
#   ----------------------------------------------------------------------------
DEFS := -D_USB_HOST

#   ----------------------------------------------------------------------------
#   All compiler options to be passed to the command line
#   ----------------------------------------------------------------------------
ALL_CFLAGS := -c $(INCLUDES) $(CFLAGS) $(EXTRA_FLAGS) $(DEFS) 

LDFLAGS :=    -L$(LIBUSB_LIBDIR) -Wl,--hash-style=gnu -Wl,-O1 

#   ----------------------------------------------------------------------------
#   Compiler and Linker procedure
#   From this point and on changes are very unlikely.
#   ----------------------------------------------------------------------------
.PHONY: all debug release clean
ifeq (${debug}, 1)
all: debug
else
all: release
endif

#   ----------------------------------------------------------------------------
#   Building  
#   ----------------------------------------------------------------------------
debug: $(OBJDIR)/$(BIN)
release: $(OBJDIR)/$(BIN)

$(OBJDIR)/$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)  -Wl,-Map,$(OBJDIR)/$(NAME).map

$(OBJDIR)/%.o : %.c $(HDRS)
	@mkdir -p $(OBJDIR)
	$(CC) $(DEFS) $(ALL_CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJDIR)
