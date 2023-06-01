#include <ncurses.h>
#include <string.h>

char the_board[8][8] = {
    {'*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', 'X', 'O', '*', '*', '*'},
    {'*', '*', '*', 'O', 'X', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*'},
    {'*', '*', '*', '*', '*', '*', '*', '*'}
};


int main(int argc, char **argv) {

    if(strcmp(argv[1], "") == 0)
        
    initscr();
    cbreak();
    noecho();
    // Display the game board
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            mvprintw(row, col * 2, "%c ", the_board[row][col]);
        }
    }

    // Refresh the screen
    refresh();

    // Wait for user input
    getch();

    // End ncurses mode
    endwin();

    return 0;
}