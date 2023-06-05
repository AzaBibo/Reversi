#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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
