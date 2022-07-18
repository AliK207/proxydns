CC= gcc
CFLGAS= -Wall -Wextra
INCDIR= -I ../../inc/
LIBDIR= -L ../../dynamic
LFLAGS= -Wl,--no-as-needed -ldl -lmemoire -lcunit
LDPATH= -Wl,-rpath=../../dynamic
LIB1 = -lLog1
LIB2 = -lLog2
LIBGENG = -lGenericLog
all : testLog testLogCU testGeneric testLog2

testLog: testLog.c
	$(CC) $< $(CFLAGS) $(INCDIR) $(LFLAGS) $(LIBDIR) $(LIBGENG) $(LIB1) $(LDPATH) -o $@

testLogCU: testLogCU.c
	$(CC) $< $(CFLAGS) $(INCDIR) $(LFLAGS) $(LIBDIR) $(LIBGENG) $(LIB1) $(LIB2) $(LDPATH) -o $@

testGeneric: testGeneric.c
	$(CC) $< $(CFLAGS) $(INCDIR) $(LFLAGS) $(LIBDIR) $(LIBGENG) $(LIB1) $(LIB2) $(LDPATH) -o $@

testLog2: testLog2.c
	$(CC) $< $(CFLAGS) $(INCDIR) $(LFLAGS) $(LIBDIR) $(LIBGENG) $(LIB2) $(LDPATH) -o $@


clean:
	rm -f testLog testLogCU testGeneric testLog2 *.txt
