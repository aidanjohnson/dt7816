#  Makefile to build a DT78xx executable
#   ----------------------------------------------------------------------------
#  Usage : make [debug=1] [RULES_DIR=path1] [DT78xx_DIR=path2] 
#	    [BOARD_TYPE=DT78xx] {all|clean}
#
#  If make is invoked with debug set to 1, the debug version of this application
#  is built/cleaned/installed. By default, the release version is built 
#  RULES_DIR specifies the path to the Rules.make file installed by the TI SDK.
#  DT78xx_DIR specifies the path to the DT78XX header files. 
#  If either RULES_DIR and/or DT78xx_DIR argument is absent this Makefile uses 
#  defaults
#  BOARD_TYPE selects the type of board. By default, this makefile sets it to
#  DT7837. You can override that by specifying a different BOARD_TYPE, such as
#  DT7816, in the command line.
#
#  Note that any of the above options can be set in the environment as
#  variables. To use the definition from the environment instead of this
#  makefile, invoke make with the -e (or --environment-overrides) option in 
#  the command line.
#   ----------------------------------------------------------------------------
 
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
BOARD_TYPE = DT7837
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
NAME := dig-io
SRCS := main.c
HDRS := 
OBJS :=
DEBUG :=
BIN := $(NAME)

#   ----------------------------------------------------------------------------
#   Compiler and Linker flags 
#   ----------------------------------------------------------------------------
ifeq (${debug}, 1)
OBJDIR := debug
EXTRA_FLAGS := -g3 -gdwarf-2 -Wall -D$(BOARD_TYPE)
else
OBJDIR := release
EXTRA_FLAGS := -O4 -Wall -D$(BOARD_TYPE)
endif
BINDIR := $(OBJDIR)
LIBS := $(LIBS) 
OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

#   ----------------------------------------------------------------------------
#   Compiler include directories 
#   ----------------------------------------------------------------------------
INCLUDES := -I$(COMN_DIR) -I$(DT78xx_DIR)

#   ----------------------------------------------------------------------------
#   Compiler symbol definitions 
#   ----------------------------------------------------------------------------
DEFS := 

#   ----------------------------------------------------------------------------
#   All compiler options to be passed to the command line
#   ----------------------------------------------------------------------------
ALL_CFLAGS := -c $(INCLUDES) $(CFLAGS) $(EXTRA_FLAGS) $(DEFS)

LDFLAGS :=    -Wl,--hash-style=gnu         \
              -Wl,-O1                      \

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

$(BINDIR)/$(BIN): banner $(OBJS)
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
