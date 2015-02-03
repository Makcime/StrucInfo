CC=gcc
CFLAGS=-g -pedantic -Wall
LDFLAGS=
EXEC=out

all: $(EXEC)

out: out.o ../InOut/src/inout.o
	$(CC) -o out out.o ../InOut/src/inout.o $(LDFLAGS)

out.o: ErathosteneStatic.c
	$(CC) -o out.o -c ErathosteneStatic.c -g -pedantic -Wall $(CFLAGS)

inout.o: ../InOut/src/inout.c 
	$(CC) -o inout.o -c ../InOut/src/inout.c -g -pedantic -Wall $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)