#
# Simple Makefile for compiling programs for initio robot car 
#
SHELL	= bash
GCC	= gcc
CFLAGS	= -Wall -Werror -mfloat-abi=hard
LFLAGS	= -linitio -lcurses -lwiringPi -lpthread

CROSSGCC	= arm-linux-gnueabi-gcc
CROSSINCLUDEPATH	= -I/usr/local/arm-linux-gnueabi/include

PROG 	= line_follower

.PHONY: all run cross-compile cross-link help

all: $(PROG)

run: $(PROG)
	sudo ./$<

% : %.c
	$(GCC) -o $@ $(CFLAGS) $(LFLAGS) $<

# cross compilation: compiler on host machine:
cross-compile: cross_$(PROG).o

cross_$(PROG).o: $(PROG).c
	$(CROSSGCC) -c -o cross_$(PROG).o $(CFLAGS) $(CROSSINCLUDEPATH) $<

# cross compilation: linker on target machine:
# (need to first copy compiled object file from host to target machine)
cross-link:
	$(GCC) -o cross_$(PROG) $(LFLAGS) cross_$(PROG).o

help:
	@echo
	@echo "Possible commands:"
	@echo " > make run"
	@echo " > make cross-compile"
	@echo " > make cross-link"
	@echo

