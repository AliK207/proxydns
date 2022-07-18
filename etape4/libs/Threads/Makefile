BIB=../dynamic/libthread.so
LFLAGS= -lpthread -shared -Wl

all: $(BIB)

libthread.o: libthread.c
	$(CC) $< $(CFLAGS) -c -fPIC -std=c99 

$(BIB): libthread.o
	$(CC) $< $(LFLAGS),-soname,libthread.so -o $@

clean:
	rm -f $(BIB) *.o

