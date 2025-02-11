#include <stdio.h>
#include <stdint.h>

#include "net.h"

int main(void){
	int conn = connect_net("127.0.0.1:8080");
	if (conn < 0){
		fprintf(stderr, "Failed to conn to server\n");
		return 1;
	}
	
	printf("Connected to server\n");

	char *msg = "Hello from client";
	send_net(conn, msg, 17);

	char buffer[1024];
	int bytes = recv_net(conn, buffer, sizeof(buffer) - 1);
	if (bytes > 0) {
		buffer[bytes]='\0';
		printf("received response from server: %s\n", buffer);
	}
	
	close_net(conn);
return 0;
}
