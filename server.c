/*****************************************
 *
 *   员工管理服务器 v3.0
 *   Author 	 : 石磊、代朝阳
 *   data 		 : 2020.8.13
 *   Description : Process client requests
 *
 ****************************************/

#include "server.h"

int main(int argc, const char *argv[])
{
	struct sockaddr_in cin;
	socklen_t addrlen = sizeof(cin);
	int fd = -1;
	int newfd = -1;
	pid_t pid;

	/*打开数据库,存在就打开，不存在就创建*/
	if(sqlite3_open(MSGBASE,&db) != SQLITE_OK)
	{
		printf("%s\n",sqlite3_errmsg(db));
		return -1;
	}else{
		printf("open MSGBASE success...\n");
	}

	/*创建帐号数据表*/
	if(sqlite3_exec(db,\
				"create table if not exists usr_data(id integer primary key autoincrement,username text,passwd text,type integer);",\
				NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("create usr_data >%s\n",errmsg);
	}else{
		printf("create or open usr_data table success...\n");
	}

	/*创建员工信息表*/
	if(sqlite3_exec(db,\
				"create table if not exists emp_data(id int primary key,name text,age int,sex text,phone text,addr text);",\
				NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("create emp_data >%s\n",errmsg);
	}else{
		printf("create or open emp_data table success...\n");
	}

	/*验证用户是否存在*/
	if(sqlite3_get_table(db,"select * from usr_data where username='root';",\
				&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}else{
		printf("user message search over...\n");
	}

	if(nrow >= 1)
	{
		printf("Adminer is exists!\n");
	}
	if(nrow == 0)
	{	
		/*添加用户名、密码到用户数据表中*/
		if(sqlite3_exec(db,"insert into usr_data values(null,'root','root',0);",\
					NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
		}else{
			printf("Adminer Is Ready...\n");
		}
	}

	/*调用监听函数，监听服务器*/
	fd = listen_socket(99999,BACKLOG);
	if(0 > fd)
	{
		perror("server is leave!\n");
		return 0;
	}
	printf("wait connect...\n");

	while(1)
	{
		/*接受客户端请求*/
		newfd = accept(fd,(struct sockaddr *)&cin,&addrlen);
		if(0 > newfd){
			perror("accept error");
			return -1;
		}

		printf("accept success...\n");

		if(0 > (pid = fork()))
		{
			perror("fork create error");
			return -1;
		}else if(pid == 0)
		{
			/*子进程不需要使用fd*/
			close(fd);
			/*客户端连接信息*/
			client_info(cin);
			client_data_ctl(&newfd);
			return 0;
		}else{
			/*子进程结束后父进程关闭newfd*/
			close(newfd);
		}
	}
	close(fd);
	return 0;
}

/*********************************************************
 * Function Name  : client_info
 * Description    : printf client connect info
 * Input          : sockaddr
 * Output         : None
 * Return         : None
 * *******************************************************/
void client_info(struct sockaddr_in cin)
{
	char ipv4_addr[16];

	bzero(ipv4_addr,sizeof(ipv4_addr));

	if(NULL == inet_ntop(AF_INET,(void*)&cin.sin_addr.s_addr,\
				ipv4_addr,sizeof(ipv4_addr)))
	{
		perror("inet_ntop");
	}

	printf("+++++ client(%s:%d)id connected +++++\n",ipv4_addr,ntohs(cin.sin_port));
}

/*********************************************************
 * Function Name  : client_data_ctl
 * Description 	  : Process client requests
 * Input          : socket
 * Output         : None
 * Return         : None
 * *******************************************************/
int client_data_ctl(void *arg)
{
	MSG *usrMsg = (MSG *)malloc(sizeof(MSG));
	int newfd = *(int *)arg;
	int ret = -1;

	while(1)
	{
		memset(usrMsg,0,sizeof(MSG));
		ret = recv(newfd,usrMsg,sizeof(MSG),0);

		if(ret <= 0)
		{
			perror("recv error");
			return -1;
		}
		printf("++++++ wait choose ++++++\n");
		switch(usrMsg->flags[0])
		{
		case REGISTER:
			usr_register(newfd,usrMsg); /*用户注册*/
			break;
		case LOGIN:
			usr_login(newfd,usrMsg); /*用户登录*/
			break;
		case FIND:
			passwd_find(newfd,usrMsg); /*查找用户密码*/
			break;
		case QUIT:
			printf("client is leave...\n");
			return;
			break;
		default:
			printf("make choice error!\n");
			break;
		}
	}
	free(usrMsg);
	return;
}

