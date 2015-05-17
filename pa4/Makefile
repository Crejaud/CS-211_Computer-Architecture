COMPILER = gcc
CCFLAGS = -Wall -ansi -pedantic
all: comb
comb: comb.o
	$(COMPILER) $(CCFLAGS) -lm -o comb comb.o
comb.o: comb.c comb.h
	$(COMPILER) $(CCFLAGS) -c comb.c
clean:
	rm -f comb comb.o

