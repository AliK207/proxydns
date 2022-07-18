LIBDIR1= -L../libs/static
LIBDIR2= -L../libs/dynamic
LIB= -lreseau -lGenericLog -lthread -lmemoire -ldl
BIN=../bin
TARGET=$(BIN)/proxy
LDPATH= -Wl,-rpath=../libs/dynamic

all: $(TARGET)

main.o: main.c 
	$(CC) $(CFLAGS) -c $<

args.o: args.c 
	$(CC) $(CFLAGS) -c $<

$(TARGET): main.o  args.o
	$(CC) $(CFLAGS) main.o args.o -o $@ $(LIBDIR1) $(LIBDIR2) $(LIB) $(LDPATH)
	
clean: 
	rm -f $(TARGET) *.o
