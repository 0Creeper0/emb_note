#ifndef __PROTO_H
#define __PROTO_H

#define RCV_IP		"192.168.0.100"
#define RCVPORT		1234

#define NAMESIZE	32

typedef struct {
	int8_t id;
	char name[NAMESIZE];
} msg_t;

#endif
