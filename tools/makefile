ROOT = ../
BUILD = ./build/
LIB = tools
LIBPATH_O = $(BUILD)$(LIB).o
LIBPATH_SO = $(BUILD)lib$(LIB).so
INSTPATH = $(ROOT)lib/

CC = gcc
STD ?= -std=c99
WFLAGS ?= -Wall
CFLAGS ?= -c -fPIC -I$(ROOT)headers
LDFLAGS ?= --shared

all: clean $(LIBPATH_SO)

install:
	mkdir -p $(INSTPATH) && cp $(LIBPATH_SO) $(INSTPATH)

clean:
	rm -f  $(LIBPATH_SO)
	rm -f $(LIBPATH_O)

$(LIBPATH_SO): $(LIBPATH_O)
	$(CC) $(LIBPATH_O) $(STD) $(WFLAGS) $(LDFLAGS) -o $(@)
	rm -f $(LIBPATH_O)

$(LIBPATH_O): $(LIB).c
	mkdir -p $(BUILD)
	$(CC) $(LIB).c $(STD) $(WFLAGS) $(CFLAGS) -o $(@)
