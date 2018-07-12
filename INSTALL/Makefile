#   ----------------------------------------------------------------------------
#  Makefile to build a web server application executing in the DT78xx.
#  This uses the libmongoose library from http://cesanta.com/. Details are at
#  http://cesanta.com/docs.shtml
#
#  Usage : make [debug=1] [RULES_DIR=path1] [DT78xx_DIR=path2] 
#	    [COMN_DIR=path3] [FFTW_DIR=path4] [BOARD_TYPE=DT78xx]  {all|clean}
#
#  If make is invoked with debug set to 1, the debug version of this application
#  is built/cleaned/installed. By default, the release version is built 
#  RULES_DIR specifies the path to the Rules.make file installed by the TI SDK.
#  DT78xx_DIR specifies the path to the DT78XX header files. 
#  FFTW_DIR specifies the path to FFTW header and library files. !!!You must
#   specify this
#  COMN_DIR is the directory where DT78xx examples common files are.
#  BOARD_TYPE specifies the board type. Defaults to DT7837
#  If either RULES_DIR/DT78xx_DIR/COMN_DIR argument is absent this Makefile uses 
#  defaults
#    
#   ----------------------------------------------------------------------------
#   Included defined variables
#   ----------------------------------------------------------------------------

# Path to Rules.make. Edit if this Makefile is moved elsewhere or assign the
# path in the command line
RULES_DIR = ../../..
# Path to directory with DT78xx header file. Edit if this Makefile is 
# moved elsewhere or assign the path in the command line
DT78xx_DIR = ../../../board-support/extra-drivers/dt78xx/
# Path to common files
COMN_DIR = ../common
# Board type
BOARD_TYPE = DT7816
#----------------------------------------------------------------------------
include $(RULES_DIR)/Rules.make
VPATH = $(COMN_DIR)
CFLAGS ?=
CROSS_COMPILE ?=

#   ----------------------------------------------------------------------------
#   Name of the Linux compiler
#   ----------------------------------------------------------------------------
CC := $(CROSS_COMPILE)gcc

#   ----------------------------------------------------------------------------
#   General options, sources and libraries
#   ----------------------------------------------------------------------------
NAME := recorder
SRCS := main.c dt78xx_aio.c dt78xx_misc.c libaiff.c aifx.c extended.c float32.c g711.c iff.c lpcm.c pascal.c RingBuf.c sunriset.c recorder_helpers.c
HDRS := 
OBJS :=
DEBUG :=
BIN := $(NAME)


#  ----------------------------------------------------------------------------
#   Compiler and Linker flags 
# To enable NEON vectorization, specify -ftree-vectorize and -mfpu=neon on the 
# compiler command line. Compiling at optimization level -O3 implies 
# -ftree-vectorize is implicit. To get more information about the vectorizations
# the compiler is performing, or is unable to perform because of possible 
# dependencies, specify -ftree-vectorizer-verbose on the command line. This 
# parameter takes an integer value specifying the level of detail to provide, 
# where 1 enables additional printouts and higher values add even more 
# information.
#  ----------------------------------------------------------------------------
FPU_FLAGS := -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 \
	-ftree-vectorizer-verbose=0
ifeq (${debug}, 1)
OBJDIR := debug
EXTRA_FLAGS := -g3 -gdwarf-2 -Wall
else
OBJDIR := release
EXTRA_FLAGS := -O4 -Wall 
endif
BINDIR := $(OBJDIR)
LIBS := $(LIBS) -lpthread -lm
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

#   ----------------------------------------------------------------------------
#   Compiler include directories 
#   ----------------------------------------------------------------------------
INCLUDES := -I$(COMN_DIR) -I$(DT78xx_DIR)

#   ----------------------------------------------------------------------------
#   Compiler symbol definitions 
#   ----------------------------------------------------------------------------
DEFS := -std=gnu99  $(FPU_FLAGS) -D$(BOARD_TYPE)

#   ----------------------------------------------------------------------------
#   All compiler options to be passed to the command line
#   ----------------------------------------------------------------------------
ALL_CFLAGS := -c $(INCLUDES) $(CFLAGS) $(EXTRA_FLAGS) $(DEFS)

LDFLAGS :=    -Wl,--hash-style=gnu         \
              -Wl,-O1                      

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
debug: $(BINDIR)/$(BIN)
release: $(BINDIR)/$(BIN)

$(BINDIR)/$(BIN): banner $(OBJS) Makefile
	$(CC) -o $@ $(OBJS) $(LIBS) $(LDFLAGS)  -Wl,-Map,$(BINDIR)/$(NAME).map

$(OBJDIR)/%.o : %.c $(HDRS)
	@mkdir -p $(OBJDIR)
	$(CC) $(DEFS) $(ALL_CFLAGS) -o $@ $<

clean:
	@rm -rf $(OBJDIR)

banner:
	@echo --------------------------------------
	@echo    Building $(BIN) for $(BOARD_TYPE)
	@echo --------------------------------------
