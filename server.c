#include "functions.h"

int main (int argc, char const **argv) 
{	
	if (argc != 2) {
		fprintf(stderr, "Wrong number of arguments") ;
		exit(EXIT_FAILURE) ;
	}

	int conn_fd = listen_at_port(atoi(argv[1])) ;
	chat_server(conn_fd) ;

	shutdown(conn_fd, SHUT_RDWR) ;
} 