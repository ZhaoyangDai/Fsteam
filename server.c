#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define BACKLOG 30
#define DATABASE "emp_ctl.db"
/**************************************
 *   员工管理服务器 v1.0
 *   开发者：石磊、代朝阳
 * 功能：接收客户端请求，与客户端进行通讯
 *管理维护用户密码表、员工信息表、历史记录表
 *
 *
 ***************************************/
/*员工信息结构体*/
int do_register(int newfd,data_t usrMsg,sqlite3 *db);
int do_login(int newfd,data_t usrMsg,sqlite3 *db);

typedef struct{
	char name[20];
	char sex[10];
	int year;
	double salary;
	char department[20];
	double telephone;
	char E_mail[30];
	char address[100];
	char history[50];
	char warn[50];
}empinfo_t;

/*帐号信息结构体*/
typedef struct {
	char usrname[20];
	char usrpsw[20];
	char usrerr[50];
	empinfo_t info;
}data_t;
/*请求信息结构体*/
typedef struct{
	int protocol;
	data_t data;
}DATA;

/***********************************
 * 监听函数
 * 功能：通过接口监听
 * 参数：端口号
 *       监听数
 * 返回值：成功返回 0
 * 	 	   失败返回-1
 *
 ***********************************/
int listen_socket(const unsigned int port,int backlog ){

	int fd = -1;
	int b_reuse = 1;

	/*创建套接字*/
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > fd){
		perror("socket create error");
		return -1;
	}

	/*允许快速重用*/
	if(0 != setsockopt(fd,SOL_SOCKET,SO_REUEsin,\
				(void *)&b_reuse,sizeof(int))){
		perror("reuse error");
		exit(1);
	}

	/*填充地址信息结构体*/
	struct sockaddr_in sin = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = INADDR_ANY,
	};

	/*绑定地址*/
	if(0 !=  bind(fd,(struct sockaddr *)&sin,sizeof (sin))){
		perror("bind error");
		exit(1);
	}

	/*监听*/
	if(0 != listen(fd,BACKLOG)){
		perror("listen error");
		exit(1);
	}
	printf("server begin work !\n");

	return fd;
}

int main(int argc, const char *argv[])
{
	sqlite3 *db;
	pid_t pid;
	data_t usrMsg;
	struct sockaddr_in cin;
	int fd = -1;
	int newfd = -1;
	char *errmsg;

	/*打开数据库,存在就打开，不存在就创建*/
	if(sqlite3_open(DATABASE,&db) != SQLITEOK){
		printf("%s\n",sqlite3_errmsg(db));
		return -1;
	}else{
		printf("open DATABASE success.\n");
	}

	/*创建帐号数据表*/
	if(sqlite3_exec(db,\
				"create table if not exists usr_data
		(usrname char primary key,usrpsw char);",\
			NULL,NULL,&errmsg) != SQLITE_OK){
				printf("%s\n",errmsg);
			}else{
				printf("Create or open emp_info table success.\n");
			}
	/*创建员工信息表*/
	if(sqlite3_exec(db,\
				"create table if not exists emp_info
		(name char primary key,sex char,age int,salary double,department char,
		 telephone double,E-mail char,address char,history char);",\
			NULL,NULL,&errmsg) != SQLITE_OK){
				printf("%s\n",errmsg);
			}else{
				printf("Create or open emp_info table success.\n");
			}

	/*调用监听函数，监听服务器*/
	fd = listen_socket(99999,BACKLOG);
	if(0 > fd){
		perror("server is leave.\n");
		return 0;
	}
	printf("wait for a client...\n");

	while(1)
	{
		/*接受客户端请求*/
		newfd = accept(fd,(struct sockaddr *)&cin,sizeof(cin));
		if(0 > newfd){
			perror("accept error");
			exit(1);
		}

		if(0 > (pid = fork())){
			perror("fork create error");
			return -1;
		}else if(pid == 0){
			/*子进程不需要使用fd*/
			close(fd);
			/*客户端连接信息*/
			cli_info(cin);
			cli_data_handle(&newfd);
			return 0;
		}else{
			/*子进程结束后父进程关闭newfd*/
			close(newfd);
		}
	}
	close(fd);
	return 0;
}

/*接入客户端信息*/
void client_info(struct socket_in cin)
{
	char ipv4_addr[16];
	bzero(ipv4_addr,sizeof(ipv4_addr));
	if(NULL = inet_ntop(AF_INET,(void*)&cin.sin_addr.s_addr,\
				ipv4_addr,sizeof(ipv4_addr))){
		perror("inet_ntop");
		exit(1);
	}
	printf("客户端(%s:%d)已连接>\n",ipv4_addr,ntohs(cin.sin_port));
}

//数据操作函数
void client_data_ctl(void *arg)
{
	int newfd = *((int *)arg);
	int ret = -1;
	char buf[BUFSIZ] = {};
	DATA *command;
	/***************************
	 *判断客户端是否有数据传递
	 *如果产生数据传递，执行接收
	 ****************************/
	while(1){
		/*接收客户端指令*/
		bzero(buf,BUFSIZ);
		ret = recv(newfd,command,sizeof(DATA),0);
		if(ret <= 0){
			perror("recv error");
			return -1;
		}
		printf("wait please...\n");
		switch(command->protocol){
		case 1:
			usr_register(newfd,command->data,db);
			break;
		case 2:
			usr_login(newfd,command->data,db);
			break;
		case 3:
			emp_cat(newfd,command->data->info,db);
			break;
		case 4:
			usr_update(newfd,command->data->info,db);
			break;
		case 5:
			usr_sistory(newfd,command->data->info,db);
			break;
		case 6:
			usr_change(newfd,command->data->info,db);
			break;
		case 7:
			emp_add(newfd,command->data->info,db);
			break;
		case 8:
			emp_remove(newfd,command->data->info,db);
			break;

		default:
			printf("Invalid data msg.\n");
		}
	}

	/*发送数据到客户端*/
	if(0 >= send(rwfd,buf,sizeof(buf),0)){
		perror("send error");
		return -1;
	}
}

/******************************
 * 注册
 * ***************************/
int usr_register(int newfd,data_t *usrMsg,sqlite3*db)
{
	int ret = -1;
	char * errmsg;
	char sql[300];

	/*添加用户名、密码到用户数据表中*/
	sprintf(sql,"insert into usr_data values('%s','%s');",\
			usrMsg->usrname,usrMsg->usrpsw);
	/*验证用户名是否存在*/
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(usrMsg->usrerr,"user is exist.");
	}else{
		printf("client register success.");
	}
	return 0;
}

/******************************
 * 登录
 * ***************************/
int usr_login(int newfd,data_t *usrMsg,sqlite3 *db)
{
	char *errmsg;
	char sql[300];
	/*查找用户名和查找密码*/
	sprintf(sql,"select * from usr_data where usrname='%s',usrpsw=%d;",\
			usrMsg->usrname,usrMsg->usrpsw);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(usrMsg->usrerr,"user is no find.");
	}else{
		printf("success");
	}
	return 0;
}

/*****************************
 * 员工信息表操作
 * 1.查看员工信息
 * 2.更改员工信息
 * 3.查看操作记录
 * 4.修改用户密码
 * 5.添加员工信息(root)
 * 6.删除员工信息(root)
 * 7.查看用户信息表(root)(暂时不管)
 * **************************/
/*查看员工信息*/
int emp_cat(int newfd,empinfo_t *empMsg,sqlite3 *db){
	char sql[300] = {};
	sprintf(sql,"select * from emp_info where name='%s';",empMsg->usrname);
	if(sqlite3_exec(newfd,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"get message error.");
	}else{
		printf("success");
	}
	return 0;
}

/*更新员工信息*/
int emp_update(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	sprintf(sql,"update emp_info set usrpsw='%s' where name='%s';",\
			empMsg->salary,empMsg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"message update error.");
	}else{
		printf("success");
	}
	return 0;
}

/*查看操作历史记录*/
int usr_sistory(int newfd,data_t *usrMsg,sqlite3 *db)
{
	char sql[300] = {};
	sprintf(sql,"select * from usr_data where usrname=%s,usrpsw=%d;",\
			usrMsg->usrname,usrMsg->usrpsw);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(usrMsg->usrerr,"get sistory error.");
	}else{
		printf("success");
	}
	return 0;
}

/*修改账户密码*/
int usr_change(int newfd,data_t *usrMsg,sqlite3 *db)
{
	char sql[300] = {};
	sprintf(sql,"update usr_data  set usrpsw='%s' where usrname='%s';",\
			usrMsg->usrpsw,usrMsg->usrname);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(usrMsg->usrerr,"password changed fail.");
	}else{
		printf("success");
	}
	return 0;
}

/*添加员工*/
int emp_add(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	sprintf(sql,"insert into emp_info 
			VALUES('%s','%s',%d,%d,%d,'%s','%s','%s','%s','%s');",\
			empMsg->name,empMsg->sex,empMsg->age,empMsg->year,\
			empMsg->salary,empMsg->department,empMsg->telephone,\
			empMsg->E_mail,empMsg->address,empMsg->history);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"employee is already exists.");
	}else{
		printf("success");
	}
	return 0;
}
/*删除员工*/
int emp_remove(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	sprintf(sql,"delete from emp_info where usrname='%s';",empMsg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"employee removed fail.");
	}else{
		printf("success");
	}
	return 0;
}


/*****************************
 * 密码修改
 * 1.查找用户名
 * 2.查找验证信息
 * 3.更新密码
 * 4.反馈结果给客户端
 * **************************/

usrdate;

