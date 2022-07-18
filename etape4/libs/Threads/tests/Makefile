CC= gcc
CFLGAS= -Wall -Wextra
INCDIR= -I ../../inc/ -I ../../src
LIBDIR= -L ../../dynamic
LFLAGS= -lGenericLog -lLog1 -lLog2 -ldl -lmemoire -lcunit -lthread
LDPATH= -Wl,-rpath=../../dynamic

all : testThreads

testThreads: testThreads.c
	$(CC) $< $(CFLAGS) $(INCDIR) $(LFLAGS) $(LIBDIR) $(LDPATH) -o $@

clean: 
	rm -f testThreads

