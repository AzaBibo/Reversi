#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char ** argv) {
	
    int conn_server_fd, conn_client_fd; 

    if(argc < 2) 
	    error("Invalid number of arguments");
    if (strcmp(argv[1], "-client") == 0) { // 'X'
        //TODO
        if(argc != 4) error("Invalid number of arguments");
        conn_client_fd = connect_ipaddr_port(argv[2], atoi(argv[3]));
        chat_client(conn_client_fd);
	}
    else if(strcmp(argv[1], "-server") == 0) { // 'O' #STARTS
        //TODO
        if(argc != 3) error("Invalid number of arguments");
        conn_server_fd = listen_at_port(atoi(argv[2]));
        chat_server(conn_server_fd);
    }  
    else {
	    error("Passing the wrong arguments");
    }

    getch();

    screen_end(conn_server_fd, conn_client_fd);

    return 0;
}
