#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sqlite3.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>

#include "../proto.h"

static int addIsOk(chat_t *chat);
static int showIsOk(int sd, chat_t *chat, struct sockaddr_in *client_addr, socklen_t client_addrlen);
static int msgIsOk(int sd, chat_t *chat);

int main(void)
{
	int sd;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addrlen = sizeof(client_addr);
	int ret;
	chat_t chat;
	pid_t pid;
	int val = 1;
	struct sigaction act;
	sqlite3 *db; // 类似文件描述符
	// 创建表（不存在的话）
	char *sql = "create table if not exists friTable(\
				 id integer primary key autoincrement not null, \
				 account text not null, \
				 fri_account text not null);";

	ret = sqlite3_open("./server.db", &db); // 打开数据库（不存在会自动创建）
	if (ret != SQLITE_OK) {
		perror("sqlite3_open()");
		exit(1);
	}
	ret = sqlite3_exec(db, sql, NULL, NULL, NULL); // 执行sql
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec:%s\n", sqlite3_errmsg(db));
		perror("sqlite3_exec()");
		exit(1);
	}

	sql = "create table if not exists msgTable(\
				 id integer primary key autoincrement not null, \
				 account text not null, \
				 fri_account text not null, \
				 msg text not null);";

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
	server_addr.sin_port = htons(CHAT_SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	ret = bind(sd, (void *)&server_addr, sizeof(server_addr));
	if (ret == -1) {
		perror("bind()");
		close(sd);
		exit(1);
	}

	while (1) {
		ret = recvfrom(sd, (void *)&chat, sizeof(chat), 0, (void *)&client_addr, &client_addrlen);
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
			if (chat.status == CHAT_STATUS_ADD) {
				ret = addIsOk(&chat);
				if (ret == 0) {
					chat.status = ADD_STATUS_OK;
				} else if (ret == 1) {
					chat.status = ADD_STATUS_ALREADY;
				} else if (ret == -1) {
					chat.status = ADD_STATUS_ERROR;
				}
				printf("status:%d client_addrlen:%d\n", chat.status, client_addrlen);
				sendto(sd, (void *)&chat, sizeof(chat), 0, (void *)&client_addr, client_addrlen);
			} else if (chat.status == CHAT_STATUS_SHOW) {
				showIsOk(sd, &chat, &client_addr, client_addrlen);
			} else if (chat.status == CHAT_STATUS_CHAT) {
				printf("chat mode\n");
				ret = msgIsOk(sd, &chat);
				if (ret == 0) {
					chat.status = MSG_STATUS_OK;
				} else if (ret == -1) {
					chat.status = MSG_STATUS_ERROR;
				}
				sendto(sd, (void *)&chat, sizeof(chat), 0, (void *)&client_addr, client_addrlen);
			}
			_exit(0);
		}
	}

	exit(0);
}

static int addIsOk(chat_t *chat)
{
	// 没查到				-1
	// 查到了	已经是好友	1
	// 查到了	还不是好友	0
	
	sqlite3 *db;
	int ret;
	char *sql;
	sqlite3_stmt *stmt;

	printf("account:%s\nfri_account:%s\n", chat->account, chat->fri_account);

	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	// 在regTable查找目标好友账号
	sql = "select * from regTable where account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->account, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW) {
		// 没查到或者出错
		goto STEP_ERROR;
	}

	// 查到了
	// 在friTable查找本人账号和目标好友账号
	sql = "select * from friTable where account=? and fri_account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->account, -1, NULL);
	sqlite3_bind_text(stmt, 2, chat->fri_account, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret == SQLITE_ROW) {
		// 没查到或者出错
		goto ALREADY;
	}

	// 符合新添加条件 添加好友（双向）
	sql = "insert into friTable(account, fri_account) values(?,?);";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->account, -1, NULL);
	sqlite3_bind_text(stmt, 2, chat->fri_account, -1, NULL);
	
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto STEP_ERROR;
	}

	sql = "insert into friTable(account, fri_account) values(?,?);";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->fri_account, -1, NULL);
	sqlite3_bind_text(stmt, 2, chat->account, -1, NULL);
	
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

static int showIsOk(int sd, chat_t *chat, struct sockaddr_in *client_addr, socklen_t client_addrlen)
{
	// 查询出错	-1
	// 查到了	0
	
	sqlite3 *db;
	int ret;
	char *sql;
	sqlite3_stmt *stmt;
	int i = 0;

	printf("account:%s\n", chat->account);

	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}

	// 记录ip和端口
	sql = "update loginTable set port=? where account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_int(stmt, 1, ntohs(client_addr->sin_port));
	sqlite3_bind_text(stmt, 2, chat->account, -1, NULL);
	
	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		goto STEP_ERROR;
	}

	// 查找
	sql = "select * from friTable where account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->account, -1, NULL);

	while (1) {
		ret = sqlite3_step(stmt);
		if (ret == SQLITE_ROW) {
			memcpy(&chat->fri_account, sqlite3_column_text(stmt, 2), ACCSIZE);
			chat->status = SHOW_STATUS_OK;
			sendto(sd, (void *)chat, sizeof(*chat), 0, (void *)client_addr, client_addrlen);
		} else if (ret != SQLITE_DONE) {
			// 出错
			chat->status = SHOW_STATUS_ERROR;
			sendto(sd, (void *)chat, sizeof(*chat), 0, (void *)client_addr, client_addrlen);
			goto STEP_ERROR;
		} else {
			// 查完了
			break;
		}
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

static int msgIsOk(int sd, chat_t *chat)
{
	// 发送错误				-1
	// 发送成功				0
	
	sqlite3 *db;
	int ret;
	char *sql;
	sqlite3_stmt *stmt;
	const char *fri_addr;
	int fri_port;
	struct sockaddr_in client_addr;
	socklen_t client_addrlen = sizeof(client_addr);

	printf("account:%s\nfri_account:%s\n", chat->account, chat->fri_account);

	ret = sqlite3_open("./server.db", &db);
	if (ret != SQLITE_OK) {
		return -1;
	}


	// 在loginTable查找目标是否在线
	sql = "select * from loginTable where account=?;";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->fri_account, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_ROW) {
		// 不在线 返回错误
		printf("%d\n", __LINE__);
		goto STEP_ERROR;
	}

	// 在线 发送消息并保存
	chat->status = CHAT_STATUS_CHAT;
	fri_addr = sqlite3_column_text(stmt, 2);
	fri_port = sqlite3_column_int(stmt, 3);
	
	client_addr.sin_family = AF_INET;
	client_addr.sin_port = htons(fri_port);
	inet_aton(fri_addr, &client_addr.sin_addr);
	sendto(sd, (void *)chat, sizeof(*chat), 0, (void *)&client_addr, client_addrlen);
	sql = "insert into msgTable(account, fri_account, msg) values(?,?,?);";
	ret = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	if (ret != SQLITE_OK) {
		goto PREPARE_ERROR;
	}

	sqlite3_bind_text(stmt, 1, chat->account, -1, NULL);
	sqlite3_bind_text(stmt, 2, chat->fri_account, -1, NULL);
	sqlite3_bind_text(stmt, 3, chat->msg, -1, NULL);

	ret = sqlite3_step(stmt);
	if (ret != SQLITE_DONE) {
		printf("%d\n", __LINE__);
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
