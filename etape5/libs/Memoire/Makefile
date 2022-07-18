BIBLIOMEMOIRE= ../dynamic/libmemoire.so
LFLAGS= -shared -Wl

all: memoire.o $(BIBLIOMEMOIRE)

memoire.o: memoire.c
	$(CC) $< $(CFLAGS) -c -fPIC -std=c99

$(BIBLIOMEMOIRE): memoire.o
	$(CC) $< $(LFLAGS),-soname,libmemoire.so -o $@

clean:
	rm -f $(BIBLIOMEMOIRE) *.o




