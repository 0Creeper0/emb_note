#ifndef __TOKEN_H
#define __TOKEN_H

#define ARRSIZE 	1024
// ADT
typedef struct
{
	int token;
	int cps;
	int burst;
} token_t;

// 初始化(返回td)
int token_init(int cps, int burst);

// 取令牌
int token_get(int td, int token);

// 还令牌
int token_put(int td, int token);

// 销毁
void token_destroy(int td);

#endif
