CC=gcc
CFLAGS= -Wall -Wextra
INCDIR= -I ../../inc/
LIBDIR= -L ../../dynamic
LFLAGS= -lmemoire
LDPATH= -Wl,-rpath=../../dynamic

all: testMemory

testMemory: testMemory.c
	$(CC) $< $(CFLAGS) $(INCDIR) $(LIBDIR) $(LFLAGS) $(LDPATH) -o $@

clean:
	rm -f testMemory

