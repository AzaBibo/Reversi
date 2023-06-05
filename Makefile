.PHONY : all clean

all: reversi

functions.o: functions.c functions.h
	gcc -c functions.c -o functions.o -lncurses

reversi: functions.o reversi.c
	gcc reversi.c functions.o -g -o reversi -lncurses
	./reversi

clean:
	rm reversi *.o
	clear
