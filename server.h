#ifndef __SERVER_H__
#define __SERVER_H__

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <wait.h>
#include <sqlite3.h>

#define BACKLOG 30
#define DATABASE "emp_ctl.db"

/*员工信息结构体*/
typedef struct{
	char name[20];
	char sex[10];
	int age;
	int year;
	double salary;
	char department[20];
	char telephone[20];
	char E_mail[30];
	char address[100];
	char history[50];
	char warn[50];
	char tag[50];
	char newdata[50];
}empinfo_t;

/*帐号信息结构体*/
typedef struct {
	char usrname[20];
	char usrpsw[20];
	char usrerr[50];
	char history[100];
	empinfo_t info;
}data_t;

/*请求信息结构体*/
typedef struct{
	int protocol;
	data_t data;
}DATA;

/*客户端请求*/
void client_info(struct sockaddr_in cin);
int client_data_ctl(void *arg,sqlite3 *db);

/*用户操作*/
int usr_register(int newfd,data_t *usrMsg,sqlite3 *db);
int usr_login(int newfd,data_t *usrMsg,sqlite3 *db);

/*员工信息管理*/
int emp_cat(int newfd,empinfo_t *empMsg,sqlite3 *db);
int emp_update(int newfd,empinfo_t *empMsg,sqlite3 *db);
int usr_sistory(int newfd,data_t *usrMsg,sqlite3 *db);
int usr_change(int newfd,data_t *usrMsg,sqlite3 *db);
int emp_add(int newfd,empinfo_t *empMsg,sqlite3 *db);
int emp_remove(int newfd,empinfo_t *empMsg,sqlite3 *db);
int history_callback(void *arg,int f_num,char**f_value,char**f_name);

#endif //__SERVER_H__
