.PHONY : all clean

reversi:
	gcc reversi.c -g -o reversi -lncurses
	./reversi
clean:
	rm reversi
	clear