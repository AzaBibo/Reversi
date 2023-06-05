#include <ncurses.h>
#include <string.h>

void printBoard(char the_board[8][8]) {
    int start_row = (LINES - 8) / 2;  // Calculate the starting row to center the board
    int start_col = (COLS - 8) / 2;   // Calculate the starting column to center the board

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            if (the_board[row][col] == '*') {
                attron(A_BLINK);                    // Enable blinking attribute
                mvaddch(start_row + row, start_col + col, '*');  // Print blinking asterisk
                attroff(A_BLINK);                   // Disable blinking attribute
            } else if (the_board[row][col] == 'X') {
                attron(COLOR_PAIR(1) | A_BOLD);     // Set color pair 1 (white on black) and enable bold attribute
                mvaddch(start_row + row, start_col + col, 'X');  // Print black 'X'
                attroff(COLOR_PAIR(1) | A_BOLD);    // Disable color pair and bold attribute
            } else if (the_board[row][col] == 'O') {
                attron(COLOR_PAIR(2) | A_BOLD);     // Set color pair 2 (black on white) and enable bold attribute
                mvaddch(start_row + row, start_col + col, 'O');  // Print white 'O'
                attroff(COLOR_PAIR(2) | A_BOLD);    // Disable color pair and bold attribute
            }
        }
    }
}

int main() {
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();

    // Enable blinking mode
    curs_set(0);  // Hide the cursor
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);  // Color pair 1: white on black
    init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Color pair 2: black on white

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

    // Print the game board with blinking asterisks, black 'X' and white 'O'
    printBoard(the_board);

    // Refresh the screen to show the changes
    refresh();

    // Wait for a key press
    getch();

    // End ncurses mode
    endwin();

    return 0;
}
