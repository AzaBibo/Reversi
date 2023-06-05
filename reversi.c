#include <ncurses.h>
#include <string.h>

void screen_start() {
	cbreak();
	noecho();
	curs_set(0);
	start_color();

	init_color(COLOR_PAIR(3), 500, 500, 500); //GREy
	init_pair(1, COLOR_RED, COLOR_BLACK); // 'X' for now
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); // 'O' for now
	init_pair(4, COLOR_BLUE, COLOR_BLACK); // '*' for now
}

int main(int args, char ** argv) {
    // Initialize ncurses
    initscr();
    screen_start();

    if(args < 2) 
	    error("Invalid number of arguments");
    if (strcmp(argv[1], "-client") == 0) { // 'X'
	//TODO
	if(argc != 3) error("Invalid number of arguments");
    	printBoard(the_board);
	}
    else if(strcmp(argv[1], "-server") == 0) { // 'O' #STARTS
   	//TODO
	if(args != 4) error("Invalid number of arguments");
    	printBoard(the_board);
    }  
    else {
	error("Passing the wrong arguments");
    }


    getch();

    endwin();

    return 0;
}
