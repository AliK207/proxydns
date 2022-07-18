LFLAGS = ../../static/libreseau.a
all: testlibReseau

testlibReseau: test_libreseau.c 
	$(CC) $< $(CFLAGS) $(LFLAGS) -o $@

clean:
	rm -f testlibReseau
