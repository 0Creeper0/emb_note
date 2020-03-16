#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "proto.h"

int main(void)
{
	int sd, newsd, cnt, fd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen;
	msg_t msgbuf;
	char buf[MSGSIZE] = {};

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_aton(SERVER_IP, &server_addr.sin_addr);

	if (bind(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	if (listen(sd, 20) == -1) {
		perror("listen()");
		exit(1);
	}

	while(1) {
		newsd = accept(sd, (struct sockaddr *)&client_addr, &client_addrlen);
		if (newsd == -1) {
			perror("accept()");
			close(sd);
			exit(1);
		}

		cnt = read(newsd, &msgbuf, sizeof(msgbuf));

		if(cnt == -1) {
			perror("read()");
			exit(1);
		}

		strncpy(buf, msgbuf.msg, cnt);
		puts(buf);

		fd = open(buf, O_RDONLY);
		if (fd == -1) {
			// 不存在
			msgbuf.flag = 0;
			send(newsd, &msgbuf, sizeof(msgbuf), 0);
		} else {
			while (1) {
				cnt = read(fd, buf, MSGSIZE);
				if (cnt == -1) {
					if (errno == EINTR)
						continue;
					perror("read()");
					exit(1);
				}
				if (cnt == 0)
					break;

				msgbuf.flag = 1;
				strncpy(msgbuf.msg, buf, cnt);
				send(newsd, &msgbuf, sizeof(msgbuf), 0);
			}
		}
		close(newsd);
	}

	close(sd);

	exit(0);
}
