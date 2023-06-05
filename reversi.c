#include <ncurses.h>
#include <string.h>
#include "functions.h"

int main(int argc, char ** argv) {

    screen_start();

    if(argc < 2) 
	    error("Invalid number of arguments");
    if (strcmp(argv[1], "-client") == 0) { // 'X'
	//TODO
	if(argc != 3) error("Invalid number of arguments");
    	printBoard();
	}
    else if(strcmp(argv[1], "-server") == 0) { // 'O' #STARTS
   	//TODO
	if(argc != 4) error("Invalid number of arguments");
    	printBoard();
    }  
    else {
	error("Passing the wrong arguments");
    }


    getch();

    screen_end();

    return 0;
}
