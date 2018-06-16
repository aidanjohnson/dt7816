#   ----------------------------------------------------------------------------
#  Makefile to build a DT78xx executable
#
#  Usage : make [debug=1] [RULES_DIR=path1] [DT78xx_DIR=path2] 
#           [COMN_DIR=path3] [BOARD_TYPE=DT78xx] {all|clean}
#
#  If make is invoked with debug set to 1, the debug version of this application
#  is built/cleaned/installed. By default, the release version is built 
#  RULES_DIR specifies the path to the Rules.make file installed by the TI SDK.
#  DT78xx_DIR specifies the path to the DT78XX header files. 
#  COMN_DIR is the directory where DT78xx examples common files are.
#  BOARD_TYPE specifies the board type. Defaults to DT7837
#  If either RULES_DIR/DT78xx_DIR/COMN_DIR argument is absent this Makefile uses 
#  defaults
###############################################################################    
# Variables passed in externally
# Path to Rules.make. 
RULES_DIR = ../../..
# Path to directory with DT78xx header file. 
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
NAME := dt7816cal
SRCS := main.c dt78xx_aio.c dt78xx_misc.c
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
LIBS := $(LIBS) -lpthread
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

# Build only for DT7816. For any other board force a clean and don't build
ifeq ($(BOARD_TYPE),DT7816)
ifeq (${debug}, 1)
all: debug
else
all: release
endif
else
all: clean
	@echo $(BIN) not built for $(BOARD_TYPE)
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
