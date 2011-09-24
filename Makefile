CC=msp430-gcc
CFLAGS=-Os -Wall -std=gnu99 -g -mmcu=msp430x2231

OBJS=main.o helper_functions.o


all: $(OBJS)
	$(CC) $(CFLAGS) -o main.elf $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -fr main.elf $(OBJS)
