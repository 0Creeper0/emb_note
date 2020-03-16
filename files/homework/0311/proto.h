#ifndef __PROTO_H
#define __PROTO_H

#define SERVER_IP	"148.70.179.241"
#define SERVER_PORT	3456

#define MSGSIZE 	1024

typedef struct {
	int flag;
	char msg[MSGSIZE];
} msg_t;

#endif
