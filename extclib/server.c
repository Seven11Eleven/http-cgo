#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "net.h"

#define BUFF_SIZE 1024

int main(void) {
	int listener = listen_net("127.0.0.1:8080");
	if (listener < 0) {
		fprintf(stderr, "%d\n", listener);
		return 1;
	}

	printf("server is listening 127.0.0.1:8080 ...\n");
	char buffer[BUFF_SIZE];

	while(1) {
		int conn = accept_net(listener);
		if (conn < 0){
			fprintf(stderr, "Error: accept\n");
			return 3;
		}
		while(1){
			int length = recv_net(conn, buffer, BUFF_SIZE);
			if (length <= 0) {
				break;
			}
			printf("received: %s\n", buffer);
			for (int i = 0; i < length; ++i){
				buffer[i] = toupper((unsigned char)buffer[i]);
			}
			send_net(conn, buffer, length);
		}
		close_net(conn);
	}
}
