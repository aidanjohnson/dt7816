# Makefile to build USB host and device applications in this directory

all: 
	$(MAKE) -C ./board
	$(MAKE) -C ./host
	
clean:	
	$(MAKE) -C ./board clean
	$(MAKE) -C ./host clean

.PHONY: all clean
