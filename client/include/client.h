#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>                                                             
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define REGISTER 	1 		//注册
#define LOGIN 	 	2 		//登录
#define FIND 		3 		//忘记密码
#define QUIT 		15 		//退出

#define REG_SUC 	4 		//注册成功
#define LOGIN_SUC 	5 		//登录成功
#define CHECK_OK 	14 		//校验成功

#define ADD_USER 	6 		//添加用户
#define DELE_USER 	7 		//删除用户
#define CGE_USER 	8 		//修改用户
#define INQ_INFO 	9 		//查询信息
#define INQ_HIS 	10 		//查询历史

#define DELE_SUC 	11 		//删除用户成功
#define CGE_SUC 	12 		//修改用户成功

#define CGE_PSW 	13 		//修改密码
#define ERROR 		66 		//错误
typedef struct {
	int  id;             	//员工的编号                                                                                                                                   
	char name[20]; 			//员工姓名
	char username[20]; 		//用户名
	char passwd[20]; 		//密码
	int flags[2];      	//用于传送命令
	char sex[10];
	int  age;
	char phone[11];
	char addr[50];
	int type[2];
}MSG;
MSG msg;

int socketfd; 		//网络套接字
struct sockaddr_in serveraddr; 		//网络信息结构体

void register_func(int ,MSG *);
void login_root(int ,MSG *);
void add_user(int ,MSG *);
void login_func(int ,MSG *);
void dele_user(int ,MSG *);
void inq_info(int , MSG *);
void cge_psw(int ,MSG *);
void login_user(int ,MSG *);
void find_psw(int , MSG *);

#endif
