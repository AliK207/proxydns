CC = gcc
CFLAGS = -Wall -Wextra
INCL = -I ../../inc -I ../../src
LIBDIR = -L../../dynaminc
LFLAGS =  -lshmem
LDPATH = -Wl,-rpath=../../dynamic


all : testshm

testshm : testshm.c
	$(CC) $< $(CFLAGS) $(INCL) $(LIBDIR) $(LFLAGS)  $(LDPATH) -o $@

clean : 
	rm -f testshm


