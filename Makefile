CC = g++
CFLAGS = -O2
TARGET = main.out
OBJS = main.o board.o

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o : main.cc
board.o : board.cc

clear:
	rm -f *.o main.out
