#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


#include "proto.h"

int main(int argc, char *argv[])
{
	int sd, cnt, fd;
	struct sockaddr_in server_addr;
	msg_t msgbuf;


	if (argc != 2)
		exit(1);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	inet_aton(SERVER_IP, &server_addr.sin_addr);

	if(connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect()");
		close(sd);
		exit(1);
	}

	strncpy(msgbuf.msg, argv[1], MSGSIZE);

	send(sd, &msgbuf, sizeof(msgbuf), 0);

	cnt = read(sd, &msgbuf, MSGSIZE);
	if (cnt == -1) {
		perror("read()");
		exit(1);
	}

	if (msgbuf.flag) {
		//文件存在 接收
		fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (fd == -1) {
			perror("open()");
			exit(1);
		}

		write(fd, msgbuf.msg, cnt);
		while (1) {
			cnt = read(sd, &msgbuf, MSGSIZE);
			if (cnt == -1) {
				if (errno == EINTR)
					continue;
				perror("read()");
				exit(1);
			}
			if (cnt == 0)
				break;

			write(fd, msgbuf.msg, cnt);
		}
		close(fd);
	} else {
		printf("file doesn't exsit\n");
	}

	close(sd);

	exit(0);
}
