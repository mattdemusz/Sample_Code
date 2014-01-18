CC = gcc
CCFLAGS = -Wall -g
ARKEYS = rv
TARGET = SearchTool

all: SearchTool
SearchTool: main.o prefixTree.o helpers.o
	$(CC) $(CCFLAGS) -o SearchTool main.o prefixTree.o helpers.o
main.o: main.c
	$(CC) $(CCFLAGS) -c main.c
prefixTree.o: prefixTree.c
	$(CC) $(CCFLAGS) -c prefixTree.c
helpers.o: helpers.c
	$(CC) $(CCFLAGS) -c helpers.c
	
clean:
	rm -f sl *.o SearchTool
