APPNAME = merge_sort
ROOT = ../

LIB = -ltestsuit -ltools 
LIBPATH = $(ROOT)lib
HEADERPATH = $(ROOT)headers
CC = gcc
STD ?= -std=c99
WFLAGS ?= -Wall
CFLAGS ?= -I$(HEADERPATH) -L$(LIBPATH)
LDFLAGS ?= $(LIB) -Wl,-rpath=$(LIBPATH)

all: clean $(APPNAME).out

$(APPNAME).out: $(APPNAME).c
	$(CC) $(APPNAME).c $(STD) $(WFLAGS) $(CFLAGS) $(LDFLAGS) -o $(@)

clean:
	rm -f $(APPNAME).out
