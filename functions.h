#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <linux/socket.h>

void printBoard();

void screen_start();

void screen_end(int server, int client);

void help();

void error(char * message);

int listen_at_port (int portnum);

void chat_server (int conn_fd);

int connect_ipaddr_port (const char * ip, int port);

void chat_client (int conn_fd);

#endif
