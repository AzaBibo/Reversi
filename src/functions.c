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
	error("User quit the game");

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

	int dir[8][2] = {
		{0, -1}, // up
		{0, 1}, // down
		{-1, 0}, // left
		{1, 0}, // right
		{-1, -1}, // up-left
		{-1, 1}, // up-right
		{1, -1}, // down-left
		{1, 1} // down-right
	};

	int flag = 0;
	for (int i = 0; i < 8; i++) {
		int x_dir = dir[i][0];
		int y_dir = dir[i][1];

		int x_temp = x + x_dir;
		int y_temp = y + y_dir;

		if (x_temp < 0 || x_temp > 7 || y_temp < 0 || y_temp > 7)
			continue;

		if (the_board[y_temp][x_temp] == xo)
			continue;

		while (the_board[y_temp][x_temp] != '*') {
			x_temp += x_dir;
			y_temp += y_dir;

			if (x_temp < 0 || x_temp > 7 || y_temp < 0 || y_temp > 7)
				break;

			if (the_board[y_temp][x_temp] == xo) {
				flag = 1;
				break;
			}
		}

		if (flag == 1)
			break;
	}

	if (flag == 0)
		return -1;
	
	point[0] = x;
	point[1] = y;
	
	return 0;
}

void changeBoard(char (*the_board)[8], int *point, char xo) {
	int x = point[0];
	int y = point[1];

	the_board[y][x] = xo;

	int dir[8][2] = {
		{0, -1}, // up
		{0, 1}, // down
		{-1, 0}, // left
		{1, 0}, // right
		{-1, -1}, // up-left
		{-1, 1}, // up-right
		{1, -1}, // down-left
		{1, 1} // down-right
	};

	for (int i = 0; i < 8; i++) {
		int x_dir = dir[i][0];
		int y_dir = dir[i][1];

		int x_temp = x + x_dir;
		int y_temp = y + y_dir;

		if (x_temp < 0 || x_temp > 7 || y_temp < 0 || y_temp > 7)
			continue;

		if (the_board[y_temp][x_temp] == xo)
			continue;

		while (the_board[y_temp][x_temp] != '*') {
			x_temp += x_dir;
			y_temp += y_dir;

			if (x_temp < 0 || x_temp > 7 || y_temp < 0 || y_temp > 7)
				break;

			if (the_board[y_temp][x_temp] == xo) {
				while (the_board[y_temp - y_dir][x_temp - x_dir] != xo) {
					the_board[y_temp - y_dir][x_temp - x_dir] = xo;
					x_temp -= x_dir;
					y_temp -= y_dir;
				}
				break;
			}
		}
	}
}

int pass(char (*the_board)[8], char xo)
{
	int flag = 0;
	int temp_point[2];
	for (int i = 0; i < 8 && flag == 0; i++) {
		for (int j = 0; j < 8 && flag == 0; j++) {
			if (the_board[i][j] == '*') {
				temp_point[0] = j * 2 + 5;
				temp_point[1] = i * 2 + 5;
				if (checkWhetherValid(the_board, temp_point, xo) == 0)
					flag = 1;
			}
		}
	}
	return flag;
}

int endgame(char (*the_board)[8])
{
	int flag = 1;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (the_board[i][j] == '*') {
				flag = 0;
				break;
			}
		}
	}
	return flag;
}

int countBoard(char (*the_board)[8], char xo)
{
	int count = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8 ; j++) {
			if (the_board[i][j] == xo)
				count++;
		}
	}

	return count;
}

int listen_at_port (int portnum) 
{
	int sock_fd = socket(AF_INET /*IPv4*/, SOCK_STREAM /*TCP*/, 0 /*IP*/) ;
	if (sock_fd == 0)
		error("socket failed");
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0)
		error("setsockopt failed");

	struct sockaddr_in address ; 
	bzero(&address, sizeof(address)); 	
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY /* localhost */ ; 
	address.sin_port = htons(portnum); 

	if (bind(sock_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
		error("bind failed");

	if (listen(sock_fd, 16 /* the size of waiting queue*/) < 0)
		error("listen failed");

	int addrlen = sizeof(address); 
	int conn_fd = accept(sock_fd, (struct sockaddr *) &address, (socklen_t*)&addrlen) ;
	if (conn_fd < 0)	
		error("accept failed") ;
	return conn_fd ;
}

int connect_ipaddr_port (const char * ip, int port)
{
	int sock_fd ;
	sock_fd = socket(AF_INET, SOCK_STREAM, 0) ;
	if (sock_fd <= 0)
		error("socket failed");
	int opt = 2 ;
	if (setsockopt(sock_fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt)) != 0)
		error("setsockopt failed");

	struct sockaddr_in address;
	bzero(&address, sizeof(address));
	address.sin_family = AF_INET; 
	address.sin_port = htons(port); 
	if (inet_pton(AF_INET, ip, &address.sin_addr) <= 0)
		error("inet_pton failed");

	if (connect(sock_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
		error("connect failed");
	return sock_fd;
}

void chat_server (int conn_fd) 
{
	char (*server_board)[8] = initBoard();
	screen_start(server_board);
	int point[2] = {5, 5};

	mvprintw(0, 0, "Partner turn                                                                          ");
	refresh();

	if (recv(conn_fd, point, 8, 0) == 0)
		error("recv failed");

	changeBoard(server_board, point, 'X');
	printBoard(server_board);

	point[0] = point[0] * 2 + 5;
	point[1] = point[1] * 2 + 5;

	while(1)
	{
		networking(conn_fd, server_board, 'O', point);
	}
	endwin();

}


void chat_client (int conn_fd)
{
	char (*clinet_board)[8] = initBoard();
	screen_start(clinet_board);
	int point[2] = {5, 5};

	while(1)
	{
		networking(conn_fd, clinet_board, 'X', point);
	}

	endwin();
}

void networking(int conn_fd, char (*the_board)[8], char xo, int *point)
{
	int check = 0;
	char opponent = (xo == 'X') ? 'O' : 'X';
	if (pass(the_board, xo) == 0)
		check = 1;
	do {
		if (check == 1) 	// pass
			break;
		else if (check == 0)
			mvprintw(0, 0, "You are '%c'. Now X's turn, X's move (yx): ", xo);
		else if(check == -1)
			mvprintw(0, 0, "Invalid move, try again.");
		else if (check == -2)
			mvprintw(0, 0, "This place is already marked!                                          ");
		refresh();

		pickBoard(point);
		keypad(stdscr, FALSE);
		check = checkWhetherValid(the_board, point, xo);
	}while(check != 0);

	changeBoard(the_board, point, xo);

	printBoard(the_board);
	send(conn_fd, point, 8, 0);
	refresh();

	if (endgame(the_board) == 1) {
		if (countBoard(the_board, xo) > countBoard(the_board, opponent))
			mvprintw(0, 0, "You win!                                                                             ");
		else if (countBoard(the_board, xo) < countBoard(the_board, opponent))
			mvprintw(0, 0, "You lose!                                                                            ");
		else if (countBoard(the_board, xo) == countBoard(the_board, opponent))
			mvprintw(0, 0, "Draw!                                                                                ");
		refresh();
		while(1)
		{
			if (getch() == 'q')
				break;
		}
		endwin();
		exit(EXIT_SUCCESS);
	}

	mvprintw(0, 0, "Partner turn                                                                          ");
	refresh();


	if (recv(conn_fd, point, 8, 0) == 0)
		error("recv failed");
	
	changeBoard(the_board, point, opponent);
	printBoard(the_board);
	if (endgame(the_board) == 1) {
		if (countBoard(the_board, xo) > countBoard(the_board, opponent))
			mvprintw(0, 0, "You win!                                                                             ");
		else if (countBoard(the_board, xo) < countBoard(the_board, opponent))
			mvprintw(0, 0, "You lose!                                                                            ");
		else if (countBoard(the_board, xo) == countBoard(the_board, opponent))
			mvprintw(0, 0, "Draw!                                                                                ");
		refresh();
		while(1)
		{
			if (getch() == 'q')
				break;
		}
		endwin();
		exit(EXIT_SUCCESS);
	}
	point[0] = point[0] * 2 + 5;
	point[1] = point[1] * 2 + 5;
}

void help() {
    printf("Description of Reversi Game:\n");
    printf("A host will be color black \"X\"\n");
    printf("A connecting user will be color white \"O\"\n");
}

void error(char *message) {
	endwin();
    printf("%s\n", message);
    exit(EXIT_FAILURE);
}
