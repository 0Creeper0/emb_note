#ifndef __PROTO_H
#define __PROTO_H

#define PATHNAME	"/etc/passwd"
#define PRO_ID		'a'

#define MSGSIZE	1024

struct msg_st {
	long mtype;
	char msg[MSGSIZE];
};

#endif
