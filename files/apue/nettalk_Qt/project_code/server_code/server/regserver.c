#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <sqlite3.h>

#include "../proto.h"

int regIsOk(reg_t *reg)
{
	printf("account:%s\npasswd:%s\nemail:%s\nphone:%s\n", reg->account, reg->passwd, reg->email, reg->phone);
	sqlite3 *db;
	int ret;
	char *sql = "select * from regTable where account=?";
	sqlite3_stmt *stmt;

	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); // 准备数据
	if (ret != SQLITE_OK) {
		goto PREPAER_ERROR;
	}

	sqlite3_bind_text(stmt, 1, reg->account, -1, NULL); // 1为？的编号， 从1开始

	// SQLITE_ROW	查到了
	// SQLITE_DONE	没查到
	ret = sqlite3_step(stmt); // 执行stmt(实质执行sql查询)
	if (ret != SQLITE_DONE) {
		// 查到或者出错
		goto STEP_ERROR;
	}

	// 可以注册
	sql = "insert into regTable(account, passwd, email, phone) values(?,?,?,?)";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPAER_ERROR;
	}

	sqlite3_bind_text(stmt, 1, reg->account, -1, NULL);
	sqlite3_bind_text(stmt, 2, reg->passwd, -1, NULL);
	sqlite3_bind_text(stmt, 3, reg->email, -1, NULL);
	sqlite3_bind_text(stmt, 4, reg->phone, -1, NULL);

	// SQLITE_DONE	成功
	ret = sqlite3_step(stmt); //执行插入
	if (ret != SQLITE_DONE) {
		goto STEP_ERROR;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

PREPAER_ERROR:
	sqlite3_close(db);
	return -1;
STEP_ERROR:
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return -1;
	return 0;
}

int main(void)
{
	int sd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	int ret;
	pid_t pid;
	reg_t reg;
	struct sigaction act;

	sqlite3 *db; // 类似文件描述符
	// 创建表（不存在的话）
	char *sql = "create table if not exists regTable(\
				 id integer primary key autoincrement not null, \
				 account text not null, \
				 passwd text not null, \
				 email text not null, \
				 phone text not null);";

	ret = sqlite3_open("./server.db", &db); // 打开数据库（不存在会自动创建）
	if (ret != SQLITE_OK) {
		perror("sqlite3_open()");
		exit(1);
	}
	ret = sqlite3_exec(db, sql, NULL, NULL, NULL); // 执行sql
	if (ret != SQLITE_OK) {
		fprintf(stderr, "%s\n", sqlite3_errmsg(db));
		perror("sqlite3_exec()");
		exit(1);
	}

	sqlite3_close(db);
	// 子进程不变僵尸
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(REG_SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	if (bind(sd, (void *)&server_addr, sizeof(server_addr)) == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	while(1) {
		ret = recvfrom(sd, (void *)&reg, sizeof(reg), 0, (void *)&client_addr, &client_addrlen);
		if (ret == -1) {
			perror("recvfrom()");
			continue;
		}

		pid = fork();
		if (pid < 0) {
			perror("fork()");
			continue;
		}
		if (pid == 0) {
			ret = regIsOk(&reg);
			if (ret == 0) {
				reg.status = REG_STATUS_OK;
			} else if (ret == -1) {
				reg.status = REG_STATUS_ALREADY;
			}
			sendto(sd, (void *)&reg, sizeof(reg), 0, (void *)&client_addr, sizeof(client_addr));
			_exit(0);
		}
	}

	exit(0);
}
