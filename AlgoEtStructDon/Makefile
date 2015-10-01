CC=g++
CFLAGS= -pedantic -Wall
CFLAGS_99= -g -pedantic -Wall -std=c99
LDFLAGS= -lm

# utils
IO = InOut/src/inout

# Exo
HELLO = hello/hello

PASCAL = pascal/pascal
ERA = ErathosteneDyna/ErathosteneDyna


TARGET_BIN = $(HELLO).x
TARGET_BIN += $(PASCAL).x
TARGET_BIN += $(ERA).x

TARGET_OBJ = $(HELLO).o
TARGET_OBJ += $(PASCAL).o
TARGET_OBJ += $(ERA).o

TARGET_OBJ += $(IO).o

all: $(TARGET_BIN)


#hELLO
$(HELLO).x: $(HELLO).o 
	$(CC) -o $(HELLO).x $(HELLO).o  $(LDFLAGS)

$(HELLO).o: $(HELLO).cpp
	$(CC) -o $(HELLO).o -c $(HELLO).cpp $(CFLAGS)

#Pascal
$(PASCAL).x: $(PASCAL).o 
	$(CC) -o $(PASCAL).x $(PASCAL).o  $(LDFLAGS)

$(PASCAL).o: $(PASCAL).cpp
	$(CC) -o $(PASCAL).o -c $(PASCAL).cpp $(CFLAGS)

#ErathosteneDyna
$(ERA).x: $(ERA).o $(IO).o
	$(CC) -o $(ERA).x $(ERA).o $(IO).o $(LDFLAGS)

$(ERA).o: $(ERA).cpp
	$(CC) -o $(ERA).o -c $(ERA).cpp $(CFLAGS)

#InOut
$(IO).o: $(IO).cpp
	$(CC) -o $(IO).o -c $(IO).cpp $(CFLAGS)


clean:
	rm -rf $(TARGET_BIN)
	rm -rf $(TARGET_OBJ)

mrproper: clean
	rm -rf $(TARGET_BIN)
	rm -rf $(TARGET_BIN)