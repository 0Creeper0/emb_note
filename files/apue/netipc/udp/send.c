#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in rtnaddr;
	msg_t msg;

	if (argc != 3)
		exit(1);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	rtnaddr.sin_family = AF_INET;
	rtnaddr.sin_port = htons(RCVPORT);
	inet_aton(RCV_IP, &rtnaddr.sin_addr);

	msg.id = atoi(argv[1]);
	strncpy(msg.name, argv[2], NAMESIZE);

	if (sendto(sd, &msg, sizeof(msg), 0, (struct sockaddr *)&rtnaddr, sizeof(rtnaddr)) == -1) {
		perror("sendto()");
		close(sd);
		exit(1);
	}

	close(sd);

	exit(0);
}
