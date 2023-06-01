#include <ncurses.h>
#include <string.h>

void printBoard(char the_board[8][8]) {
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (strcmp("*", &the_board[row][col]) == 0) {
                attron(A_BLINK);  // Enable blinking attribute
            }
            mvprintw(row, col * 2, "%c ", the_board[row][col]);
            attroff(A_BLINK);  // Disable blinking attribute
        }
    }
    refresh();
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    // Enable blinking mode
    curs_set(0);  // Hide the cursor
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Set default color pair
    init_pair(2, COLOR_WHITE, COLOR_BLACK);  // Set blinking color pair
    wbkgd(stdscr, COLOR_PAIR(1));  // Set default color pair

    // Create the game board
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

    // Print the game board with blinking asterisks
    while (true) {
        printBoard(the_board);
        napms(500);  // Sleep for 500 milliseconds (0.5 seconds)
        clear();
        napms(500);  // Sleep for 500 milliseconds (0.5 seconds)
    }

    // End ncurses mode
    endwin();

    return 0;
}
