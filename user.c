#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"user.h"

#define USER_FILE "user.dat"

user *first_user = NULL;

//����û� 
void add_user()
{
	char try_again = 'y';
	user *p = NULL;
	user *new_user = (user*)malloc(sizeof(user));
	while(try_again == 'y')
	{
		memset(new_user, 0, sizeof(user));                 //��ʼ��
		new_user->next = NULL;
		printf("load...\n");
		input_user(&(new_user->ui));
		p = find_user(new_user->ui.username);              //�����û����Է�����û����� 
		if(p == NULL){
			p = get_last_user();
			p->next = new_user;
			break;
		} 
		printf("\nsuccess\n");
		printf("�Ƿ��ٴμ��룺y or n :");
		getchar();
		try_again = getchar();
		if(try_again != 'y'){
			free(new_user);
		}
	}
}


//�����û� 
void search_user()
{
	char input = 'y';
	char username[MAX_USERNAME] = {0};
	user *p = NULL;
	while(input == 'y')
	{
		printf("load...");
		printf("\n�������û�����");
		scanf("%s", username);
		p = find_user(username);
		if(p == NULL){
			printf("failed");
			printf("�Ƿ��ٴβ��� y or n:");
			getchar();
			input = getchar();
			continue;
		} 
		show_user(&(p->ui));
		printf("success");
		printf("��dɾ������u���£�");
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

//�û���ɾ�� 
void delete_user(user *p)
{
	char input = 'N';
	user *previous = NULL;
	printf("�Ƿ�ȷ��ɾ��");
	getchar();
	input = getchar();
	if(input == 'y'){
		previous = get_previous_user(p);
		previous->next = p->next;
		free(p);
		p = NULL;
	}
}

//�����û�����Ϣ 
void update_user(user *p)
{
	char input = 'y';
	user *exist_p = NULL;
	user_info *new_p = (user_info*)malloc(sizeof(user_info));//����ռ� 
	while(input == 'y')
	{
		memset(new_p, 0, sizeof(user_info));                 //��ʼ�� 
		input_user(new_p); 
		exist_p =find_user(new_p->username);                 //��ѯ�û� 
		if(exist_p != NULL && exist_p != p){
			printf("�Ѵ���,�Ƿ��������� y or n:");
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
	free(new_p);                                           //�ͷſռ� 
}

void save_users()
{
	save_users_to_file();
	printf("success\n");
	getchar();
	getchar();
}

//�����û���Ϣ���ļ� 
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

//ϵͳ����admin�Ĺ���Ա 
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

//��ǰ�����û���Ϣ 
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

//��¼���� 
USER_TYPE login()
{
	char username[MAX_USERNAME] = {0};
	char password[MAX_PASSWORD] = {0};
	char try_again = 'y';
	user *p = NULL;
	while(try_again == 'y')
	{
		printf("\n�������û�����");
		scanf("%s", username);
		printf("���������룺");
		scanf("%s", password);
		p = find_user(username);
		if(p == NULL){
			printf("�û��������������������"); 
		}
		else if(strcmp(p->ui.password,password) != 0){
			printf("�����������");
		}
		else{
			return p->ui.user_type;
		}
		printf("�Ƿ��������� y or n:");
		getchar();
		try_again = getchar();
	}
	exit(0);
 } 
 
 //����û���Ϣ 
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
 
 //����û���Ϣ 
 void view_user()
 {
 	user *p = NULL;
	char input = 'y';
	int c = 0;
	while(input == 'y')
	{
		c = 0;
		p = first_user;
		printf("  �û���  |   ����   |   ����   |\n");
		printf("---------------------------------\n");
		while(p != NULL)
		{
			printf("%10s|%10s|%10d|",p->ui.username,p->ui.password,p->ui.user_type);
			printf("\n---------------------------------\n");
			c++;
			if(c == 5){
				c = 0;
				printf("�Ƿ�������� y or n:");
				getchar();
				input = getchar();
				if(input != 'y'){
					break;
				}
			}
			p = p->next;
		 }
		 printf("�Ƿ�Ҫ�ٴ���� y or n :");
		 getchar();
		 input = getchar(); 
	}
 }
 
 
 //��ȡ���һ���ڵ� 
 user *get_last_user()
 {
 	user *p = first_user;
 	while((p != NULL) && (p->next != NULL))
 	{
 		p = p->next;
	 }
	 return p;
 }
 
 //��ȡ����ڵ��ǰһ���ڵ� 
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
 
 //��ʾ���� 
 void show_user(user_info *info)
 {
 	printf("�û�����%s\n", info->username);
 	printf("���룺%s\n", info->password);
 	printf("�û����ͣ�%s\n", info->user_type == ADMIN ? "admin" : "user");
 }
 
 //�����û���Ϣ 
 void input_user(user_info *info)
 {
 	printf("�������û�����");
 	scanf("%s", info->username);
 	printf("���������룺");
 	scanf("%s", info->password);
 	printf("�������û����ͣ�%d�ǹ���Ա��%d���û�:", ADMIN, USER);
 	scanf("%d", &(info->user_type));
 }
 
 //�����û����� 
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
