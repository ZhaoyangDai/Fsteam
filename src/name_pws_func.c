/***************************************************               
 * Name:       name_pws_func.c
 * Data:       2020.8.7
 * Description:用户名和密码函数
 * Author:     shilei
 *
 *************************************************/
#include "client.h"
/*
 * Name:        string_func
 * Description: 判断输入的字符串是否在0-9、a-z、A-Z之间,成功返回0，失败返回1
 * Inputs:      str
 *
 */
int string_func(char *str)
{
	int i;
	for(i=0;i<strlen(str);i++){
		if(!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))){
			return 1;
		}
	}
	return 0;
}

void name_func(char *username)
{
	char name[100];
	while(1)
	{
		memset(name,0,sizeof(name));
		printf("请输入用户名\n");
		//从stdin中获取用户名
		fgets(name,sizeof(name),stdin);
		//在数组结尾添加\0
		name[strlen(name)-1] = '\0';
		if(strlen(name) == 0){
			printf("请输入用户名\n");
			continue;
		}

		if(string_func(name) == 1){
			printf("名字非法，请重新输入！\n");
			continue;
		}else
			break;
	}
	strcat(username,name);
	return;
}

void psw_func(char *userpsw)
{
	char psw[100];
	while(1)
	{
		memset(psw,0,sizeof(psw));
		printf("请输入密码：\n");
		fgets(psw,sizeof(psw),stdin);
		psw[strlen(psw)-1] = '\0';
		if(string_func(psw) == 1){
			printf("密码非法，请重新输入！\n");
			continue;
		}else
			break;
	}
	strcat(userpsw,psw);
	return;
}
