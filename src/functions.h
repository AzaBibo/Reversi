#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/socket.h>

char (*initBoard())[8];

void printBoard(char (*the_board)[8]);

void screen_start(char (*the_board)[8]);

void screen_end(int server, int client);

void pickBoard(int *point);

int checkWhetherValid(char (*the_board)[8], int *point, char xo);

void help();

void error(char * message);

int listen_at_port (int portnum);

void chat_server (int conn_fd);

int connect_ipaddr_port (const char * ip, int port);

void chat_client (int conn_fd);

#endif
