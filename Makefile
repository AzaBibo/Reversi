.PHONY : all clean

reversi:
	gcc reversi.c -g -lncurses 

clean:
	rm -rf .o
	clear