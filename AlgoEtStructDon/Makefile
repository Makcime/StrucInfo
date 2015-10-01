CC=g++
CFLAGS= -pedantic -Wall
CFLAGS_99= -g -pedantic -Wall -std=c99
LDFLAGS= -lm

# utils

# Exo
HELLO = hello/hello


TARGET_BIN = $(HELLO).x

TARGET_OBJ = $(HELLO).o

all: $(TARGET_BIN)


#hELLO
$(HELLO).x: $(HELLO).o 
	$(CC) -o $(HELLO).x $(HELLO).o  $(LDFLAGS)

$(HELLO).o: $(HELLO).cpp
	$(CC) -o $(HELLO).o -c $(HELLO).cpp $(CFLAGS)


clean:
	rm -rf $(TARGET_BIN)
	rm -rf $(TARGET_OBJ)

mrproper: clean
	rm -rf $(TARGET_BIN)
	rm -rf $(TARGET_BIN)