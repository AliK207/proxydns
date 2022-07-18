LFLAGS= -L../static
BIBLIOTHEQUE=../static/libreseau.a

all: libreseau.o $(BIBLIOTHEQUE) 

libreseau.o: libreseau.c
	$(CC) $(CFLAGS) $(LFLAGS) -c $< 

$(BIBLIOTHEQUE): libreseau.o
	ar rcs $@ $<

clean: 
	rm -f $(BIBLIOTHEQUE) libreseau.o
