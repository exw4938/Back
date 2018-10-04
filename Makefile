CC=gcc
CFLAGS=-Wall -Wextra -pedantic -ggdb
DEPS=config.h
VPATH=src

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

back: back.o config.o
	$(CC) -o back back.o config.o

clean:
	rm *.o back
