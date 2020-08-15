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
#define MSGBASE "emp_ctl.db"

#define REGISTER    1       /*注册 		*/
#define LOGIN       2       /*登录 		*/
#define FIND        3       /*忘记密码 	*/
#define QUIT        15      /*退出 		*/

#define REG_SUC     4       /*注册成功*/
#define LOGIN_SUC   5       /*登录成功*/
#define CHECK_OK    14      /*校验成功*/

#define ADD_USER    6       /*添加用户*/                                        
#define DELE_USER   7       /*删除用户*/
#define CGE_USER    8       /*修改用户*/
#define INQ_INFO    9       /*查询信息*/
#define INQ_HIS     10      /*查询历史*/

#define DELE_SUC    11      /*删除用户成功*/
#define CGE_SUC     12      /*修改用户成功*/

#define CGE_PSW     13      /*修改密码 	*/
#define ERROR       66      /*错误 		*/

typedef struct {
	int  id;                /*user/employee id 	*/
	char username[20];      /*user name 		*/
	char passwd[20];        /*user password 	*/
	int  type[2]; 			/*user owner 		*/
	char name[20];          /*employee name 	*/
	int  age; 				/*employee age 		*/
	char sex[10]; 			/*employee sex 		*/
	char phone[11]; 		/*employee phone 	*/
	char addr[50]; 			/*employee addr 	*/
	int  flags[2];       	/*return flag 		*/
}MSG;

sqlite3 *db;
int nrow;
int ncloumn;
char **resultp;
char *errmsg;

/*服务器监听函数*/
int listen_socket(const unsigned int port,int backlog );

/*客户端请求处理函数*/
void client_info(struct sockaddr_in cin);
int client_data_ctl(void *arg);

/*用户管理函数*/
void usr_register(int, MSG*);
void usr_login(int, MSG *);
void login_win(int, MSG*);
void passwd_find(int, MSG*);
void is_root(MSG *);

/*员工管理函数*/
void emp_remove(int, MSG *);
void emp_cat(int, MSG *);
void emp_data_update(int, MSG *);
void passwd_change(int, MSG* );

#endif //__SERVER_H__
