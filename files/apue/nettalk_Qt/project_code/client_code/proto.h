#ifndef __PROTO_H
#define __PROTO_H

#define DEF_SERVER_IP   "192.168.0.104"
#define DEF_SERVER_PORT 6666

// 注册
#define	REG_SERVER_IP	DEF_SERVER_IP
#define REG_SERVER_PORT DEF_SERVER_PORT

#define ACCSIZE 	20
#define PWDSIZE		128
#define EMAILSIZE	128
#define PHONESIZE	128

#define REG_STATUS_OK		0
#define REG_STATUS_ALREADY	1

typedef struct {
	char account[ACCSIZE];
	char passwd[PWDSIZE];
	char email[EMAILSIZE];
	char phone[PHONESIZE];
    int status;
} reg_t;

// 登录
#define LOGIN_SERVER_IP     DEF_SERVER_IP
#define LOGIN_SERVER_PORT   6667

#define ACCSIZE 	20
#define PWDSIZE		128

#define LOGIN_STATUS_OK         2
#define LOGIN_STATUS_ALREADY    3
#define LOGIN_STATUS_ERROR	    4

#define LOGIN                   5
#define LOGOUT                  6

typedef struct {
    char account[ACCSIZE];
    char passwd[PWDSIZE];
    int status;
} log_t;

// 聊天 添加好友
#define CHAT_SERVER_IP		DEF_SERVER_IP
#define CHAT_SERVER_PORT	6668

#define ACCSIZE 	20
#define FRISIZE 	20
#define MSGSIZE		1024

#define CHAT_STATUS_SHOW	    7
#define CHAT_STATUS_ADD 		8
#define CHAT_STATUS_CHAT	    9

#define ADD_STATUS_OK			10
#define ADD_STATUS_ALREADY		11
#define ADD_STATUS_ERROR	    12

#define SHOW_STATUS_OK			13
#define SHOW_STATUS_ERROR	    14

#define MSG_STATUS_OK			15
#define MSG_STATUS_ERROR	    16

typedef struct {
    char account[ACCSIZE];
	char fri_account[FRISIZE];
    char msg[MSGSIZE];
    int status;
} chat_t;


#endif
