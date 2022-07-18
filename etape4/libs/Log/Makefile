BIBLIOTHEQUE1=../dynamic/libLog1.so
BIBLIOTHEQUE2=../dynamic/libLog2.so
BIBLIOTHEQUEG=../dynamic/libGenericLog.so
LFLAGS= -shared -Wl


all: $(BIBLIOTHEQUEG) $(BIBLIOTHEQUE1) $(BIBLIOTHEQUE2)

libLog1.o: libLog1.c
	$(CC) $(CFLAGS) -c -fPIC -std=c99 -ldl $< 

libLog2.o: libLog2.c
	$(CC) $(CFLAGS) -c -fPIC -std=c99 -ldl $< 

libGenericLog.o : libGenericLog.c
	$(CC) $(CFLAGS) -c -fPIC -std=c99 -ldl $< 

$(BIBLIOTHEQUE1): libLog1.o
	$(CC) $(LFLAGS),-soname,libLog1.so -o  $@ $< 

$(BIBLIOTHEQUE2): libLog2.o
	$(CC) $(LFLAGS),-soname,libLog2.so -o  $@ $< 

$(BIBLIOTHEQUEG) : libGenericLog.o
	$(CC) $(LFLAGS),-soname,libGenericLog.so -o $@ $<

clean: 
	rm -f $(BIBLIOTHEQUE1) $(BIBLIOTHEQUE2) $(BIBLIOTHEQUEG) libGenericLog.o libLog1.o libLog2.o ../../bin/*.txt
