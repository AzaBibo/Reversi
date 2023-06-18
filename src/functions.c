#include "functions.h"

char (*initBoard())[8] {
    static char the_board[8][8] = {
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', 'X', 'O', '*', '*', '*'},
        {'*', '*', '*', 'O', 'X', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'},
        {'*', '*', '*', '*', '*', '*', '*', '*'}
    };
    return the_board;
}

void printBoard(char (*the_board)[8]) {
    // int start_row = (LINES - 8) / 2;  // Calculate the starting row to center the board
    // int start_col = (COLS - 8) / 2;   // Calculate the starting column to center the board

	int start_row = 5;  // Calculate the starting row to center the board
    int start_col = 5;   // Calculate the starting column to center the board

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


void screen_start(char (*the_board)[8]) {
	initscr();
	noecho();
	cbreak();
	curs_set(2);
	
	start_color();
	init_color(COLOR_PAIR(3), 500, 500, 500); //GREy
	init_pair(1, COLOR_RED, COLOR_BLACK); // 'X' for now
	init_pair(2, COLOR_YELLOW, COLOR_BLACK); // 'O' for now
	init_pair(4, COLOR_BLUE, COLOR_BLACK); // '*' for now

	printBoard(the_board);
}

void screen_end(int server, int client) {
    endwin();
    shutdown(server, SHUT_RDWR);
    shutdown(client, SHUT_RDWR);
}

void pickBoard(int *point) {
	int x = point[0];
	int y = point[1];

	keypad(stdscr, TRUE);

	move(y, x);
	refresh();

	refresh() ;
	int c ;
	while ((c = getch()) != 'q') {
		switch (c) {
			case KEY_UP:
				y-- ;
				break ;

			case KEY_DOWN:
				y++ ;
				break ;

			case KEY_LEFT:
				x-- ;
				break ;

			case KEY_RIGHT:
				x++ ;
				break ;

			default:
				if (isalpha(c)) {
					point[0] = x;
					point[1] = y;
					return;
				}
				break ;
		}

		move(y, x) ;
		refresh() ;
	}
	endwin();
	exit(1);
}

int checkWhetherValid(char (*the_board)[8], int *point, char xo) {
	int x = point[0];
	int y = point[1];

	// check if a move is vaild
	if (x % 2 == 0 || y % 2 == 0)
		return -1;

	x = (x - 5) / 2;
	y = (y - 5) / 2;

	// check if a move is vaild
	if (x < 0 || x > 7 || y < 0 || y > 7)
		return -1;
	else if (the_board[y][x] != '*')
		return -2;

	the_board[y][x] = xo;

	point[0] = x;
	point[1] = y;
	return 0;
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
	char (*server_board)[8] = initBoard();
	screen_start(server_board);
	int point[2] = {5, 5};
	int check= 0; 	// check whether valid move

	mvprintw(0, 0, "Partner turn                                                                          ");
	refresh();

	if (recv(conn_fd, point, 8, 0) == 0)
		check = -10;

	server_board[point[1]][point[0]] = 'X';
	printBoard(server_board);
	point[0] = point[0] * 2 + 5;
	point[1] = point[1] * 2 + 5;

	while(1)
	{
		if (check == 0)
			mvprintw(0, 0, "You are 'O'. Now X's turn, X's move (yx): ");
		else if(check == -1)
			mvprintw(0, 0, "Invalid move, try again.");
		else if (check == -2)
				mvprintw(0, 0, "This place is already marked!                                          ");

		refresh();

		pickBoard(point);
		keypad(stdscr, FALSE);
		check = checkWhetherValid(server_board, point, 'O');
		if (check < 0)
			continue;
		printBoard(server_board);
		refresh();
		send(conn_fd, point, 8, 0);

		mvprintw(0, 0, "Partner turn                                                                          ");
		refresh();
	

		if (recv(conn_fd, point, 8, 0) == 0)
			break;
		
		server_board[point[1]][point[0]] = 'X';
		printBoard(server_board);
		point[0] = point[0] * 2 + 5;
		point[1] = point[1] * 2 + 5;
		check = 0;
	}
	endwin();

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
	char (*clinet_board)[8] = initBoard();
	screen_start(clinet_board);
	int point[2] = {5, 5};
	int check= 0; 	// check whether valid move
	while(1)
	{
		if (check == 0)
			mvprintw(0, 0, "You are 'X'. Now X's turn, X's move (yx): ");
		else if(check == -1)
			mvprintw(0, 0, "Invalid move, try again.");
		else if (check == -2)
				mvprintw(0, 0, "This place is already marked!                                          ");
		mvprintw(10, 0, "%d - %d", point[0], point[1]);
		refresh();

		pickBoard(point);
		keypad(stdscr, FALSE);
		check = checkWhetherValid(clinet_board, point, 'X');
		if (check < 0)
			continue;
		printBoard(clinet_board);
		refresh();
		mvprintw(0, 0, "Partner turn                                                                          ");
		refresh();
	
		send(conn_fd, point, 8, 0);

		if (recv(conn_fd, point, 8, 0) == 0)
			break;
		
		clinet_board[point[1]][point[0]] = 'O';
		printBoard(clinet_board);
		point[0] = point[0] * 2 + 5;
		point[1] = point[1] * 2 + 5;
		check = 0;
	}

	endwin();
}
