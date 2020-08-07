#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define BACKLOG 30
 /**************************************
 *   员工管理服务器 v1.0
 *   开发者：石磊、代朝阳
 * 功能：接收客户端请求，与客户端进行通讯
 *管理维护用户密码表、员工信息表、历史记录表
 *
 *
 ***************************************/

typedef struct {
	char usrname[20];
	char usrpsw[20];
	EmpMsg info;
}data_t;

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

	struct sockaddr_in cin;
	int fd = -1;
	int newfd = -1;

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
			/*子进程*/
			close(fd);
			cli_info(cin);
			cli_data_handle(&newfd);
			return 0;
		}else{
			/*父进程*/
			close(newfd);
		}

	}
	close(fd);
	return 0;
}

/*接入客户端信息*/
void client_info()
{

}
//数据操作函数
void client_data_ctl(void *arg)
{
	int newfd = *((int *)arg);
	int ret = -1;
	char cbuf[BUFSIZ] = {};
	 /***************************
	 *判断客户端是否有数据传递
	 *如果产生数据传递，执行接收
	 ****************************/
	while(1){
		/*接收客户端指令*/
		bzero(cbuf,BUFSIZ);
		cliCmd = recv(newfd,buf,sizeof(buf),0);
		if(recvCmd <= 0){
			perror("recv error");
			return -1;
		}
		printf("wait please...\n");
		switch(cliCmd){
		case 1:
			//数据库操作函数
			xxx;
			break;
		case 2:
			xxx;
			break;

		}


	}




	/*发送数据到客户端*/
	if(0 >= send(rwfd,buf,sizeof(buf),0)){
		perror("send error");
		return -1;
	}
}
