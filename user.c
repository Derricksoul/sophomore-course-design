#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user.h"

#define USER_FILE "user.dat"

user *first_user = NULL;

//添加用户 
void add_user()
{
	char try_again = 'y';
	user *p = NULL;
	user *new_user = (user*)malloc(sizeof(user));
	while(try_again == 'y')
	{
		memset(new_user, 0, sizeof(user));                 //初始化
		new_user->next = NULL;
		printf("load...\n");
		input_user(&(new_user->ui));
		p = find_user(new_user->ui.username);              //查找用户，以防添加用户重名 
		if(p == NULL){
			p = get_last_user();
			p->next = new_user;
			break;
		} 
		printf("\nsuccess\n");
		printf("是否再次加入：y or n :");
		getchar();
		try_again = getchar();
		if(try_again != 'y'){
			free(new_user);
		}
	}
}


//查找用户 
void search_user()
{
	char input = 'y';
	char username[MAX_USERNAME] = {0};
	user *p = NULL;
	while(input == 'y')
	{
		printf("load...");
		printf("\n请输入用户名：");
		scanf("%s", username);
		p = find_user(username);
		if(p == NULL){
			printf("failed");
			printf("是否再次查找 y or n:");
			getchar();
			input = getchar();
			continue;
		} 
		show_user(&(p->ui));
		printf("success");
		printf("按d删除，按u更新：");
		getchar();
		input = getchar();
		if(input == 'd'){
			delete_user(p);
		}
		else if(input == 'u'){
			update_user(p);
		}
		printf("search anoyher y or n:");
		getchar();
		input = getchar();
	}
}

//用户的删除 
void delete_user(user *p)
{
	char input = 'N';
	user *previous = NULL;
	printf("是否确认删除");
	getchar();
	input = getchar();
	if(input == 'y'){
		previous = get_previous_user(p);
		previous->next = p->next;
		free(p);
		p = NULL;
	}
}

//更新用户的信息 
void update_user(user *p)
{
	char input = 'y';
	user *exist_p = NULL;
	user_info *new_p = (user_info*)malloc(sizeof(user_info));//申请空间 
	while(input == 'y')
	{
		memset(new_p, 0, sizeof(user_info));                 //初始化 
		input_user(new_p); 
		exist_p =find_user(new_p->username);                 //查询用户 
		if(exist_p != NULL && exist_p != p){
			printf("已存在,是否重新输入 y or n:");
			getchar();
			input = getchar();
		}
		else{
			strcpy(p->ui.username, new_p->username);
			strcpy(p->ui.password, new_p->password);
			p->ui.user_type = new_p->user_type;
			break;
		}
	}
	free(new_p);                                           //释放空间 
}

void save_users()
{
	save_users_to_file();
	printf("success\n");
	getchar();
	getchar();
}

//保存用户信息到文件 
void save_users_to_file()
{
	FILE *fp = fopen(USER_FILE, "wb");
	user *p = first_user;
	while(p != NULL)
	{
		fwrite(&(p->ui),sizeof(user_info), 1, fp);
		fseek(fp, 0, SEEK_END);
		p = p->next;
	}
	fclose(fp);
}

//系统生成admin的管理员 
void init_user()
{
	FILE *fp = NULL;
	user_info default_admin;
	strcpy(default_admin.username,"admin");
	strcpy(default_admin.password, "123");
	default_admin.user_type = ADMIN;
	fp = fopen(USER_FILE, "r");
	if(fp == NULL){
		fp = fopen(USER_FILE, "wb");
		fwrite(&default_admin, sizeof(user_info), 1, fp);
	}
	fclose(fp);
}

//提前加载用户信息 
void load_users()
{
	user *u =NULL;
	user *last = NULL;
	FILE *fp =NULL;
	int c = 0;
	u = (user*)malloc(sizeof(user));
	memset(u, 0, sizeof(user));
	u->next = NULL;
	fp = fopen(USER_FILE, "rb");
	fseek(fp, 0, SEEK_SET);
	while(fread(&(u->ui), sizeof(user_info), 1, fp) == 1)
	{
		if(first_user == NULL){
			first_user = u;
		}
		else{
			last = get_last_user();
			last->next = u;
		}
		c++;
		fseek(fp, c *sizeof(user_info), SEEK_SET);
		u = (user*)malloc(sizeof(user));
		memset(u, 0, sizeof(user));
		u->next = NULL;
	}
	free(u);
	u = NULL;
	fclose(fp);
}

//登录函数 
USER_TYPE login()
{
	char username[MAX_USERNAME] = {0};
	char password[MAX_PASSWORD] = {0};
	char try_again = 'y';
	user *p = NULL;
	while(try_again == 'y')
	{
		printf("\n请输入用户名：");
		scanf("%s", username);
		printf("请输入密码：");
		scanf("%s", password);
		p = find_user(username);
		if(p == NULL){
			printf("用户名输入错误，请重新输入"); 
		}
		else if(strcmp(p->ui.password,password) != 0){
			printf("密码输入错误");
		}
		else{
			return p->ui.user_type;
		}
		printf("是否重新输入 y or n:");
		getchar();
		try_again = getchar();
	}
	exit(0);
 } 
 
 //清空用户信息 
 void clear_users()
 {
 	user *p = NULL;
 	while(first_user != NULL)
 	{
 		if(first_user->next != NULL){
 			p = first_user;
 			first_user = first_user->next;
 			free(p);
 			p = NULL;
		 }
		 else{
		 	free(first_user);
		 	first_user = NULL;
		 }
	 }
 }
 
 //浏览用户信息 
 void view_user()
 {
 	user *p = NULL;
	char input = 'y';
	int c = 0;
	while(input == 'y')
	{
		c = 0;
		p = first_user;
		printf("  用户名  |   密码   |   类型   |\n");
		printf("---------------------------------\n");
		while(p != NULL)
		{
			printf("%10s|%10s|%10d|",p->ui.username,p->ui.password,p->ui.user_type);
			printf("\n---------------------------------\n");
			c++;
			if(c == 5){
				c = 0;
				printf("是否往下浏览 y or n:");
				getchar();
				input = getchar();
				if(input != 'y'){
					break;
				}
			}
			p = p->next;
		 }
		 printf("是否要再次浏览 y or n :");
		 getchar();
		 input = getchar(); 
	}
 }
 
 
 //获取最后一个节点 
 user *get_last_user()
 {
 	user *p = first_user;
 	while((p != NULL) && (p->next != NULL))
 	{
 		p = p->next;
	 }
	 return p;
 }
 
 //获取输入节点的前一个节点 
 user *get_previous_user(user *p)
 {
 	user *previous = first_user;
 	while(previous != NULL)
 	{
 		if(previous->next == p){
 			break;
		 }
		 previous = previous->next;
	 }
	 return previous;
 }
 
 //显示函数 
 void show_user(user_info *info)
 {
 	printf("用户名：%s\n", info->username);
 	printf("密码：%s\n", info->password);
 	printf("用户类型：%s\n", info->user_type == ADMIN ? "admin" : "user");
 }
 
 //输入用户信息 
 void input_user(user_info *info)
 {
 	printf("请输入用户名：");
 	scanf("%s", info->username);
 	printf("请输入密码：");
 	scanf("%s", info->password);
 	printf("请输入用户类型：%d是管理员，%d是用户:", ADMIN, USER);
 	scanf("%d", &(info->user_type));
 }
 
 //查找用户函数 
 user *find_user(char *name)
 {
 	user *p = first_user;
 	int f = 0;
 	while(p != NULL)
 	{
 		if(strcmp(p->ui.username, name) == 0){
 			f = 1;
 			break;
		 }
		 p = p->next;
	 }
	 if(f){
	 	return p;
	 }
	 return NULL;
 }
