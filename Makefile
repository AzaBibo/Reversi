.PHONY : all clean

reversi:
	gcc reversi.c -g -lncurses -o reversi

clean:
	rm -rf .o
	clear