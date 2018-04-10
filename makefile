CC=g++
OBJS=main.o image.o
DEBUG=-g
CFLAGS=-Wall -I. -c $(DEBUG) -O2
LFLAGS=-Wall $(DEBUG)
all: pa10
pa10: $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o pa10
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp
image.o: image.cpp image.h
	$(CC) $(CFLAGS) image.cpp

clean:
	rm -f $(OBJS) *~ pa10
