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
#include <signal.h>


#define CLI_LOGIN 		1 	//客户端请求登录
#define LOG_SUC 		2 	//登录成功
#define LOG_QUIT 		3 	//登录退出
#define LOG_SHW_INF 	4 	//查看个人信息
#define LOG_CGE_PSW 	5 	//修改密码
#define CGE_PSW_OK 		6 	//修改密码成功
#define LOG_CGE_NAME 	7 	//修改名字
#define CGE_NAME_OK 	8 	//修改名字成功
#define LOG_CGE_AGE 	9 	//修改年龄
#define CGE_AGE_OK  	10 	//修改年龄成功
#define LOG_CGE_SEX 	11 	//修改性别
#define CGE_SEX_OK 		12 	//修改性别成功
#define LOG_CGE_SAL 	13 	//修改工资
#define CGE_SAL_OK 		14 	//修改工资成功
#define LOG_CGE_DEP 	15 	//修改部门
#define CGE_DEP_OK 		16 	//修改部门成功
#define LOG_CGE_TELE 	17 	//修改电话
#define CGE_TELE_OK 	18 	//修改电话成功
#define LOG_CGE_MAIL 	19 	//修改邮箱
#define CGE_MAIL_OK 	20 	//修改邮箱成功
#define LOG_CGE_ADDR 	21 	//修改地址
#define CGE_ADDR_OK 	22 	//修改地址成功
#define LOG_SHW_HIS 	23 	//显示历史信息



typedef struct
{
	char name[20];
	char sex[10];
	int age;
	int number;
	double salary;
	char department[20];
	double telephone;
	char E_mail[30];
	char address[100];
	char history[50];
}empinfo_t;

typedef struct
{
	char username[20];
	char userpsw[20];
	empinfo_t info;
}data_t;

typedef struct
{
	int protocol;//命令位
	data_t data;
}DATA;


int string_func(char *);
void name_func(char *);
void psw_func(char *);

void login_func(DATA *, int);
void root_login_func(DATA *, int);

void show_info_func(DATA *,int);
void root_info_func(DATA *,int);
void cge_psw_func(DATA *,int);
void cge_name_func(DATA *,int);
void cge_age_func(DATA *,int);
void cge_sex_func(DATA *,int);
void cge_info_func(DATA *,int);
void show_his_func(DATA *,int);
void root_his_func(DATA *,int);
void cge_salary_func(DATA *,int);
void cge_dep_func(DATA *,int);
void cge_tele_func(DATA *,int);
void cge_mail_func(DATA *,int);
void cge_addr_func(DATA *,int);
void root_change_func(DATA *,int);

void add_user_func(DATA *,int);
void delete_user_func(DATA *,int);

void root_change_func(DATA *,int);

void show_his_func(DATA *,int);
void root_his_func(DATA *,int);
#endif
