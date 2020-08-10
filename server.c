/**************************************
 *   员工管理服务器 v1.0
 *   开发者：石磊、代朝阳
 * 功能：接收客户端请求，与客户端进行通讯
 *管理维护用户密码表、员工信息表、历史记录表
 *
 *
 ***************************************/
#include "server.h"

/***********************************
 * 服务器监听函数
 * func:create socket and listen
 * par: port
 * 		backlog
 * 返回值：成功返回 0
 * 	 	   失败返回-1
 ***********************************/
int listen_socket(const unsigned int port,int backlog )
{

	int fd = -1;
	int b_reuse = 1;

	/*创建套接字*/
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > fd)
	{
		perror("socket create error");
		return -1;
	}

	/*允许快速重用*/
	if(0 > setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,\
				(void *)&b_reuse,sizeof(int)))
	{
		perror("reuse error");
		return -1;
	}

	/*填充地址信息结构体*/
	struct sockaddr_in sin = 
	{
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = INADDR_ANY,
	};

	/*绑定地址*/
	if(0 >  bind(fd,(struct sockaddr *)&sin,sizeof (sin)))
	{
		perror("bind error");
		return -1;
	}

	/*监听*/
	if(0 > listen(fd,BACKLOG))
	{
		perror("listen error");
		return -1;
	}
	printf("server begin work !\n");

	return fd;
}

int main(int argc, const char *argv[])
{
	pid_t pid;
	sqlite3 *db;
	data_t usrMsg;
	struct sockaddr_in cin;
	int socklen = sizeof(cin);
	int fd = -1;
	int newfd = -1;
	char *errmsg;

	/*打开数据库,存在就打开，不存在就创建*/
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("%s\n",sqlite3_errmsg(db));
		return -1;
	}else{
		printf("open DATABASE success.\n");
	}

	/*创建帐号数据表*/
	if(sqlite3_exec(db,\
				"create table if not exists usr_data(id int primary key,usrname char,usrpsw char);",\
				NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("create usr_data >%s\n",errmsg);
	}else{
		printf("create or open emp_info table success.\n");
	}

	/*创建员工信息表*/
	if(sqlite3_exec(db,\
				"create table if not exists emp_info(id int primary key,name char,sex text,age int,year int,salary text,department text,telephone text,E_mail text,address text,history text);",\
				NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("create emp_info >%s\n",errmsg);
	}else{
		printf("Create or open emp_info table success.\n");
	}

	/*调用监听函数，监听服务器*/
	fd = listen_socket(99999,BACKLOG);
	if(0 > fd)
	{
		perror("server is leave.\n");
		return 0;
	}
	printf("wait for a client...\n");

	while(1)
	{
		/*接受客户端请求*/
		newfd = accept(fd,(struct sockaddr *)&cin,&socklen);
		if(0 > newfd){
			perror("accept error");
			return -1;
		}

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
			client_data_ctl(&newfd,db);
			return 0;
		}else{
			/*子进程结束后父进程关闭newfd*/
			close(newfd);
		}
	}
	close(fd);
	return 0;
}

/*客户端状态信息*/
void client_info(struct sockaddr_in cin)
{
	char ipv4_addr[16];

	bzero(ipv4_addr,sizeof(ipv4_addr));
	if(NULL == inet_ntop(AF_INET,(void*)&cin.sin_addr.s_addr,\
				ipv4_addr,sizeof(ipv4_addr)))
	{
		perror("inet_ntop");
	}
	printf("客户端(%s:%d)已连接>\n",ipv4_addr,ntohs(cin.sin_port));
}

/*客户端请求处理*/
int client_data_ctl(void *arg,sqlite3 *db)
{
	DATA *command;
	int newfd = *((int *)arg);
	int ret = -1;
	char buf[BUFSIZ] = {};
	
	/***************************
	 *判断客户端是否有数据传递
	 *如果产生数据传递，执行接收
	 ****************************/
	while(1)
	{
		/*接收客户端指令*/
		bzero(buf,BUFSIZ);
		ret = recv(newfd,command,sizeof(DATA),0);
		if(ret <= 0)
		{
			perror("recv error");
			return -1;
		}
		printf("wait please...\n");
		switch(command->protocol)
		{
		case 2:
			usr_register(newfd,&command->data,db); //用户注册
			break;
		case 1:
			usr_login(newfd,&command->data,db); //用户登录
			break;
		case 3:
			emp_cat(newfd,&command->data.info,db); //查看员工信息
			break;
		case 6:
			emp_update(newfd,&command->data.info,db); //更新员工信息
			break;
		case 4:
			usr_sistory(newfd,&command->data,db); //查看用户操作历史
			break;
		case 5:
			usr_change(newfd,&command->data,db); //更改用户密码
			break;
		case 7:
			emp_add(newfd,&command->data.info,db); //添加员工信息
			break;
		case 8:
			emp_remove(newfd,&command->data.info,db); //删除员工信息
			break;
		default:
			printf("Invalid data msg.\n");
		}
	}
}

