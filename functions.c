#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/socket.h>
#include "functions.h"

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

void printBoard() {
    int start_row = (LINES - 8) / 2;  // Calculate the starting row to center the board
    int start_col = (COLS - 8) / 2;   // Calculate the starting column to center the board

    int spacing = 2;  // Adjust the spacing between characters

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            int print_row = start_row + (row * spacing);    // Adjust the row position
            int print_col = start_col + (col * spacing);    // Adjust the column position

            if (the_board[row][col] == '*') {
                attron(COLOR_PAIR(4) | A_BLINK);
                mvaddch(print_row, print_col, '*');
                attroff(COLOR_PAIR(4) | A_BLINK);
            } else if (the_board[row][col] == 'X') {
                attron(COLOR_PAIR(1) | A_BOLD);
                mvaddch(print_row, print_col, 'X');
                attroff(COLOR_PAIR(1) | A_BOLD);
            } else if (the_board[row][col] == 'O') {
		attron(COLOR_PAIR(2) | A_BOLD);
                mvaddch(print_row, print_col, 'O');
                attroff(COLOR_PAIR(2) | A_BOLD);
            }
        }
    }
}

void help() {
    printf("Description of Reversi Game:\n");
    printf("A host will be color black \"X\"\n");
    printf("A connecting user will be color white \"O\"\n");
}

void error(char *message) {
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}
