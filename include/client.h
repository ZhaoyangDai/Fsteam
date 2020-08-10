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
#define CLI_REGIS 		2 	//客服端请求注册


#define LOG_SHW_INF 	3 	//查看个人信息
#define LOG_SHW_HIS 	4 	//显示历史信息
#define LOG_CGE_PSW 	5 	//修改密码
#define LOG_CGE_NAME 	6 	//修改名字
#define LOG_CGE_AGE 	7 	//修改年龄
#define LOG_CGE_SEX 	8 	//修改性别
#define LOG_CGE_SAL 	9 	//修改工资
#define LOG_CGE_DEP 	10 	//修改部门
#define LOG_CGE_TELE 	11 	//修改电话
#define LOG_CGE_MAIL 	12 	//修改邮箱
#define LOG_CGE_ADDR 	13 	//修改地址


#define LOG_SUC 		14	//登录成功
#define LOG_QUIT 		15	//登录退出
#define REGIS_SUC 		16 	//注册成功
#define CGE_PSW_OK 		17 	//修改密码成功
#define CGE_NAME_OK 	18	//修改名字成功
#define CGE_AGE_OK  	19 	//修改年龄成功
#define CGE_SEX_OK 		20 	//修改性别成功
#define CGE_SAL_OK 		21 	//修改工资成功
#define CGE_DEP_OK 		22 	//修改部门成功
#define CGE_TELE_OK 	23 	//修改电话成功
#define CGE_MAIL_OK 	24 	//修改邮箱成功
#define CGE_ADDR_OK 	25 	//修改地址成功


typedef struct
{
	char name[20];
	char sex[10];
	int age;
	int year;
	int number;
	double salary;
	char department[20];
	char telephone[20];
	char E_mail[30];
	char address[100];
	char warn[50];
	char tag[50];
	char newdata[50];
}empinfo_t;

typedef struct
{
	char username[20];
	char userpsw[20];
	char history[100];
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
