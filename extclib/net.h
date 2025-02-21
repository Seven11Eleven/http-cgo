#ifndef EXTCLIB_NET_H_
#define EXTCLIB_NET_H_

#include <stddef.h>

extern int listen_net(char *address);
extern int accept_net(int listener);

extern int connect_net(char *address);
extern int close_net(int conn);

extern int send_net(int conn, char *buffer, size_t size);
extern int recv_net(int conn, char *buffer, size_t size);

extern int to_upper(int c);
#endif /* EXTCLIB_NET_H_*/
