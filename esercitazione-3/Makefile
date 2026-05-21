CC=gcc
CFLAGS=-Wall -Wextra

CFILES=$(wildcard *.c)
BINARIES=$(patsubst %.c,%.out,$(CFILES))

all: $(BINARIES)

%.out: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(BINARIES)