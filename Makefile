CC=gcc
CFLAGS= -g -pedantic -Wall
CFLAGS_99= -g -pedantic -Wall -std=c99
LDFLAGS= -lm

# utils
IO = InOut/src/inout
LIST = List/src/list

# Exo
A = ErathosteneStatic/ErathosteneStatic
B = Hello/hello
C = ErathosteneDyna/ErathosteneDyna
D = Samia/EraDyna3
G = ErathosteneDynaDecompPremEval/ErathosteneDynaDecompPremEval
E = List/src/ListDemo
F = List/src/ListDemo
H = /home/max/Documents/StrucInfo/ListEval/ListEvalDemo

TARGET_BIN = $(A).x
TARGET_BIN += $(B).x
TARGET_BIN += $(C).x
TARGET_BIN += $(D).x
TARGET_BIN += $(E).x
TARGET_BIN += $(G).x
TARGET_BIN += $(H).x

TARGET_OBJ = $(A).o
TARGET_OBJ += $(B).o
TARGET_OBJ += $(C).o
TARGET_OBJ += $(D).o
TARGET_OBJ += $(E).o
TARGET_OBJ += $(G).o
TARGET_OBJ += $(LIST).o
TARGET_OBJ += $(IO).o
TARGET_OBJ += $(H).o

all: $(TARGET_BIN)

#ErathosteneDynaDecompPremEval
$(H).x: $(H).o
	$(CC) -o $(H).x $(H).o $(LIST).o $(LDFLAGS)

$(H).o: $(H).c 
	$(CC) -o $(H).o -c $(H).c $(CFLAGS_99)

#ErathosteneDynaDecompPremEval
$(G).x: $(G).o
	$(CC) -o $(G).x $(G).o $(LDFLAGS)

$(G).o: $(G).c 
	$(CC) -o $(G).o -c $(G).c $(CFLAGS_99)


#ListDemo
$(E).x: $(E).o $(LIST).o
	$(CC) -o $(E).x $(E).o $(LIST).o $(LDFLAGS)

$(E).o: $(E).c 
	$(CC) -o $(E).o -c $(E).c $(CFLAGS)


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

#List
$(LIST).o: $(LIST).c 
	$(CC) -o $(LIST).o -c $(LIST).c $(CFLAGS)

#Hello
$(B).x: $(B).o 
	$(CC) -o $(B).x $(B).o $(LDFLAGS)

$(B).o: $(B).c 
	$(CC) -o $(B).o -c $(B).c $(CFLAGS)

clean:
	rm -rf $(TARGET_BIN)
	rm -rf $(TARGET_OBJ)

mrproper: clean
	rm -rf $(TARGET_BIN)
	rm -rf $(TARGET_BIN)