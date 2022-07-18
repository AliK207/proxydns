BIBSO = ../dynamic/libshmem.so
LFLAGS= -shared -Wl
all: $(BIBSO)

libshmem.o : libshmem.c
	$(CC) $< $(CFLAGS) -I../inc -c -fPIC -std=c99 -ldl 

$(BIBSO) : libshmem.o
	$(CC)  $(LFLAGS),-soname,libshmem.so -o $@ $<

clean : 
	rm -f $(BIBSO) libshmem.o
