#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <signal.h>

#include "../proto.h"


static int loginIsOk(log_t *login, struct sockaddr_in *client_addr);
static int logout(log_t *login);
int main(void)
{
	int sd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	int ret;
	log_t login;
	pid_t pid;
	int val = 1;
	struct sigaction act;
	sqlite3 *db; // 类似文件描述符
	// 创建表（不存在的话）
	char *sql = "create table if not exists loginTable(\
				 id integer primary key autoincrement not null, \
				 account text not null, \
				 ip text not null, \
				 port int not null);";

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

	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(LOGIN_SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sd, (void *)&server_addr, sizeof(server_addr));
	if (ret == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, (void *)&login, sizeof(login), 0, (void *)&client_addr, &client_addrlen);
		if (ret == -1) {
			perror("recvfrom()");
			continue;
		}

		pid = fork();
		if (pid == -1) {
			perror("fork()");
			continue;
		}

		if (pid == 0) {
			if (login.status == LOGIN) {
				ret = loginIsOk(&login, &client_addr);
				if (ret == 0) {
					login.status = LOGIN_STATUS_OK;
				} else if (ret == 1) {
					login.status = LOGIN_STATUS_ALREADY;
				} else if (ret == -1) {
					login.status = LOGIN_STATUS_ERROR;
				}
			} else if (login.status == LOGOUT) {
				logout(&login);
			}
			printf("client_addrlen:%d\n", client_addrlen);
			sendto(sd, (void *)&login, sizeof(login), 0, (void *)&client_addr, client_addrlen);
			_exit(0);
		}
	}

	exit(0);
}

static int loginIsOk(log_t *login, struct sockaddr_in *client_addr)
{
	// 没查到				-1
	// 查到了	已经登录	1
	// 查到了	未登录		0
	sqlite3 *db;
	int ret;
	char *sql;
	sqlite3_stmt *stmt;

	printf("account:%s\npasswd:%s\n", login->account, login->passwd);

	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	sql = "select * from regTable where account=? and passwd=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, login->account, -1, NULL);
	sqlite3_bind_text(stmt, 2, login->passwd, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW) {
		// 没查到或者出错
		goto STEP_ERROR;
	}

	// 查到了 判断登录状态
	sql = "select * from loginTable where account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, login->account, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW) {
		goto ALREADY;
	}

	// 未登录
	sql = "insert into loginTable(account, ip, port) values(?,?,?);";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, login->account, -1, NULL);
	sqlite3_bind_text(stmt, 2, inet_ntoa(client_addr->sin_addr), -1, NULL);
	sqlite3_bind_int(stmt, 3, ntohs(client_addr->sin_port));
	
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto STEP_ERROR;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;


PREPARE_ERROR:
	sqlite3_close(db);
	return -1;
STEP_ERROR:
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return -1;
ALREADY:
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 1;
}

static int logout(log_t *login)
{
	sqlite3 *db;
	int ret;
	char *sql;
	sqlite3_stmt *stmt;

	printf("account:%s\n", login->account);

	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	sql = "delete from loginTable where account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, login->account, -1, NULL);
	
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto STEP_ERROR;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

PREPARE_ERROR:
	sqlite3_close(db);
	return -1;
STEP_ERROR:
	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return -1;
}
