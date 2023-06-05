#include <ncurses.h>
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
	refresh();
}

void screen_start() {
	initscr();
	cbreak();
	//noecho();
	curs_set(0);

	start_color();
	init_color(COLOR_PAIR(3), 500, 500, 500); //GREy
	init_pair(1, COLOR_RED, COLOR_BLACK); // 'X' for now
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); // 'O' for now
	init_pair(4, COLOR_BLUE, COLOR_BLACK); // '*' for now

	printBoard();
}

void screen_end(int server, int client) {
    endwin();
    shutdown(server, SHUT_RDWR);
    shutdown(client, SHUT_RDWR);
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

int listen_at_port (int portnum) 
{
	int sock_fd = socket(AF_INET /*IPv4*/, SOCK_STREAM /*TCP*/, 0 /*IP*/) ;
	if (sock_fd == 0)  { 
		perror("socket failed : "); 
		exit(EXIT_FAILURE); 
	}
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0) {
		fprintf(stderr, "fail at setsockopt\n") ;
		exit(EXIT_FAILURE) ;
	}

	struct sockaddr_in address ; 
	bzero(&address, sizeof(address)) ; 	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY /* localhost */ ; 
	address.sin_port = htons(portnum); 

	if (bind(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("bind failed: "); 
		exit(EXIT_FAILURE); 
	} 

	if (listen(sock_fd, 16 /* the size of waiting queue*/) < 0) { 
		perror("listen failed : "); 
		exit(EXIT_FAILURE); 
	} 

	int addrlen = sizeof(address); 
	int conn_fd = accept(sock_fd, (struct sockaddr *) &address, (socklen_t*)&addrlen) ;
	if (conn_fd < 0) {
		perror("accept failed: "); 
		exit(EXIT_FAILURE); 
	}
	return conn_fd ;
}

void chat_server (int conn_fd) 
{
	screen_start();
	char buf[256] ;

	do {
		int s ;
		
		while ( (s = recv(conn_fd, buf, 255, 0)) == 0 ) ;
		if (s == -1)
			break ;

		buf[s] = '\0' ;
		
		mvprintw(0, 0, "You are 'O'. Now 'X' turn, X's move (yx): "); //TODO
		printw("%s\n", buf); 
		refresh();// TODO
		//printf(">%s\n", buf) ; //TODO edit printf()
        //redirect to logic function and printBoard functions

		
		fgets(buf, 256, stdin) ;
		buf[strlen(buf) - 1] = '\0' ;
		if (strcmp(buf, "quit()") == 0)
			break ;

		send(conn_fd, buf, strlen(buf), 0) ; 
		mvprintw(0, 0, "You are 'O'. Now 'O' turn, O's move (yx): %s\n", buf); 
		refresh();//TODO

	} while (strcmp(buf, "quit()") != 0) ;
}

int connect_ipaddr_port (const char * ip, int port)
{
	int sock_fd ;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
	if (sock_fd <= 0) {
		perror("socket failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0) {
		fprintf(stderr, "fail at setsockopt\n") ;
		exit(EXIT_FAILURE) ;
	}

	struct sockaddr_in address ;
	bzero(&address, sizeof(address)) ;
	address.sin_family = AF_INET ; 
	address.sin_port = htons(port) ; 
	if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0) {
		perror("inet_pton failed : ") ; 
		exit(EXIT_FAILURE) ;
	} 

	if (connect(sock_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("connect failed : ") ;
		exit(EXIT_FAILURE) ;
	}
	return sock_fd ;
}

void chat_client (int conn_fd)
{
	screen_start();
	char buf[256] ;

	do {
		mvprintw(0, 0, "You are 'X'. Now X's turn, X's move (yx): "); 
		refresh();//TODO 
		fgets(buf, 256, stdin) ;
		buf[strlen(buf) - 1] = '\0' ;
		if (strcmp(buf, "quit()") == 0)
			break ;

		send(conn_fd, buf, strlen(buf), 0) ;
		printw("%s\n", buf); refresh(); //TODO

		int s ;
		while ((s = recv(conn_fd, buf, 1024, 0)) == 0) ;
		if (s == -1)
			break ;
		buf[s] = '\0' ;

		//printf(">%s\n", buf) ; //TODO edit printf()
		mvprintw(0, 0, "You are 'X'. Now X's turn, X's move (yx): %s", buf); 
		refresh(); //TODO
        //redirect to logic part, and call printBoard();
	} while (strcmp(buf, "quit()") != 0) ;
}
