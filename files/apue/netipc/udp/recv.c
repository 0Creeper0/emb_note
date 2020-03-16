#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "proto.h"

int main(void)
{
	int sd, cnt;
	struct sockaddr_in recv_addr, rtn_addr;
	socklen_t rtn_addrlen;
	msg_t rcvbuf;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	recv_addr.sin_family = AF_INET;
	recv_addr.sin_port = htons(RCVPORT);
	inet_aton(RCV_IP, &recv_addr.sin_addr);
	if (bind(sd, (const struct sockaddr *)&recv_addr, sizeof(recv_addr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	rtn_addrlen = sizeof(rtn_addr);
	while (1) {
		cnt = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0, (struct sockaddr *)&rtn_addr, &rtn_addrlen);
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			perror("recvfrom()");
			close(sd);
			exit(1);
		}
		printf("[%s:%d]\n", inet_ntoa(rtn_addr.sin_addr), ntohs(rtn_addr.sin_port));
		printf("%d %s\n", rcvbuf.id, rcvbuf.name);
	}

	close(sd);

	exit(0);
}
