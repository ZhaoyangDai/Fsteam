#include "server.h"

/*********************************************************
 * Function Name  : emp_remove
 * Description    : base on employee id to rm employee
 * Input          : accept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void emp_remove(int newfd,MSG *usrMsg)
{
	int ret = -1;
	char sql[300] = {};

	/*验证用户是否存在*/
	sprintf(sql,"select * from usr_data where id=%d;",usrMsg->id);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}else{
		printf("user message search over.\n");
	}

	if(nrow >= 1)
	{
		/*从员工信息表中删除数据*/
		sprintf(sql,"delete from usr_data where id=%d;",usrMsg->id);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			usrMsg->flags[0] = ERROR;
			send(newfd,usrMsg,sizeof(MSG),0);
			printf("%s\n",errmsg);
		}else{
			usrMsg->flags[0] = DELE_SUC;
			send(newfd,usrMsg,sizeof(MSG),0);
			printf("delete msg successfully!\n");
		}
	}
	if(nrow == 0){
		usrMsg->flags[0] = ERROR;
		send(newfd,usrMsg,sizeof(MSG),0);
		printf("usr is not exist!\n");	
	}
}

/*********************************************************
 * Function Name  : emp_cat
 * Description    : base on employee id to get data
 * Input          : accept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void emp_cat(int newfd,MSG *usrMsg)
{
	char sql[300] = {};

	recv(newfd,usrMsg,sizeof(MSG),0);

	sprintf(sql,"select * from emp_data where id=%d;",usrMsg->id);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}else{
		printf("msg cat successfully!\n");
	}

	if(nrow >= 1)
	{
		printf("===== get employee message success.=====\n");
		usrMsg->id = atoi(resultp[6]);
		strcpy(usrMsg->name,resultp[7]);
		usrMsg->age = atoi(resultp[8]);
		strcpy(usrMsg->sex,resultp[9]);
		strcpy(usrMsg->phone,resultp[10]);
		strcpy(usrMsg->addr,resultp[11]);
		send(newfd,usrMsg,sizeof(MSG),0);
	}
	if(nrow == 0)
	{
		memset(usrMsg,0,sizeof(MSG));
		usrMsg->flags[0] = ERROR;
		send(newfd,usrMsg,sizeof(MSG),0);
		printf("usr id not exist!\n");
	}
}

/*********************************************************
 * Function Name  : emp_data_update
 * Description    : base on employee id to update data
 * Input          : accept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void emp_data_update(int newfd,MSG *usrMsg)
{
	int ret = -1;
	char sql[300] = {};

	recv(newfd,usrMsg,sizeof(MSG),0);

	sprintf(sql,"update emp_data set age=%d,phone='%s',addr='%s' where id=%d;",\
			usrMsg->age,usrMsg->phone,usrMsg->addr,usrMsg->id);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		usrMsg->flags[0] = ERROR;
		ret = send(newfd,usrMsg,sizeof(MSG),0);
	}else{
		printf("===== data update successfully!=====\n");
		usrMsg->flags[0] = CGE_SUC;
		ret = send(newfd,usrMsg,sizeof(MSG),0);
	}
}

/*********************************************************
 * Function Name  : passwd_change
 * Description    : base on user id to change user password
 * Input          : accept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void passwd_change(int newfd,MSG *usrMsg)
{
	int ret = -1;
	char sql[300] = {};

	recv(newfd,usrMsg,sizeof(MSG),0);

	sprintf(sql,"update usr_data set passwd='%s' where id=%d;",\
			usrMsg->passwd,usrMsg->id);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		usrMsg->flags[0] = ERROR;
		send(newfd,usrMsg,sizeof(MSG),0);
	}else{
		printf("===== password change success.=====\n");
		usrMsg->flags[0] = CGE_SUC;
		send(newfd,usrMsg,sizeof(MSG),0);
	}
}

