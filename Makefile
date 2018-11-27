CFLAGS=$(shell pkg-config --cflags gtk+-3.0)
LDFLAGS=$(shell pkg-config --libs gtk+-3.0)
CC=gcc

SOURCES=$(wildcard *.c)
OBJS=$(SOURCES:.c=.o)

main: clean $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS) main
