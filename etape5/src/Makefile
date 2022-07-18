LIBDIR1= -L../libs/static
LIBDIR2= -L../libs/dynamic
LIB= -lreseau -lGenericLog -lthread -lmemoire -ldl -lshmem
BIN=../bin
TARGET=$(BIN)/proxy
TARGET2=$(BIN)/dnsproxy_mgr
LDPATH= -Wl,-rpath=../libs/dynamic

all: $(TARGET) $(TARGET2)

main.o: main.c 
	$(CC) $(CFLAGS) -c $<

args.o: args.c 
	$(CC) $(CFLAGS) -c $<

dnsproxy_mgr.o: dnsproxy_mgr.c
	$(CC) $(CFLAGS) -c $<

read.o: read.c
	$(CC) $(CFLAGS) -c $<

$(TARGET): main.o  args.o
	$(CC) $(CFLAGS) main.o args.o -o $@ $(LIBDIR1) $(LIBDIR2) $(LIB) $(LDPATH)
	
$(TARGET2): dnsproxy_mgr.o  args.o
#$(TARGET2): read.o  args.o
	$(CC) $(CFLAGS) dnsproxy_mgr.o args.o -o $@ $(LIB) $(LIBDIR1) $(LIBDIR2) $(LDPATH) 
#	$(CC) $(CFLAGS) read.o args.o -o $@

clean: 
	rm -f $(TARGET) $(TARGET2) *.o
