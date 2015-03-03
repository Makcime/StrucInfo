CC=gcc
CFLAGS=-g -pedantic -Wall
LDFLAGS= -lm

# InOut utils
IO = InOut/src/inout

# Exo
A = ErathosteneStatic/ErathosteneStatic
B = Hello/hello
C = ErathosteneDyna/ErathosteneDyna
D = Samia/EraDyna3

TARGET_BIN = $(A).x
TARGET_BIN += $(B).x
TARGET_BIN += $(C).x
TARGET_BIN += $(D).x

all: $(TARGET_BIN)


#Hello
$(B).x: $(B).o 
	$(CC) -o $(B).x $(B).o $(LDFLAGS)

$(B).o: $(B).c 
	$(CC) -o $(B).o -c $(B).c $(CFLAGS)

#ErathosteneStatic
$(A).x: $(A).o $(IO).o
	$(CC) -o $(A).x $(A).o $(IO).o $(LDFLAGS)

$(A).o: $(A).c 
	$(CC) -o $(A).o -c $(A).c $(CFLAGS)

#ErathosteneDyna
$(C).x: $(C).o $(IO).o
	$(CC) -o $(C).x $(C).o $(IO).o $(LDFLAGS)

$(C).o: $(C).c 
	$(CC) -o $(C).o -c $(C).c $(CFLAGS)

#Samia
$(D).x: $(D).o $(IO).o
	$(CC) -o $(D).x $(D).o $(IO).o $(LDFLAGS)

$(D).o: $(D).c 
	$(CC) -o $(D).o -c $(D).c $(CFLAGS)

#InOut
$(IO).o: $(IO).c 
	$(CC) -o $(IO).o -c $(IO).c $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf $(TARGET_BIN)
	rm -rf *x

mrproper: clean
	rm -rf $(TARGET_BIN)