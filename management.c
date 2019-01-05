#include<stdio.h>
#include<stdlib.h>

#include"book.h"
#include"management.h"
#include"user.h"

#define MENU_ADMIN_COUNT 12
#define MENU_SEARCH_BOOK_COUNT 6
#define MENU_USER_COUNT 8

char menu_title[]=
"------------------------------\n"
"        ͼ�����ϵͳ          \n\n";

char menu_admin[] = 
"\t1.����ͼ��\n"
"\t2.���ͼ��\n"
"\t3.�޸�ͼ��\n"
"\t4.����ͼ��\n"
"\t5.ɾ��ͼ��\n"
"\t6.����ͼ��\n"
"\t7.�����û�\n"
"\t8.�����û�\n"
"\t9.����û�\n"
"\t10.�����û�\n"
"\t11.�˳�ϵͳ\n";

void (*admin_func[]) () =
{
	add_book,
	view_book,
	update_book,
	show_search_book_menu,
	delete_book,
	save_books,
	add_user,
	search_user,
	view_user,
	save_users,
	admin_exit
};

char menu_admin_search_book[] = 
"1.����\n"
"2.����\n"
"3.������\n"
"4.��������\n"
"5.ISBN\n"
"6.�������˵�\n";

void (*admin_search_book_func[]) () =
{
	search_book_by_name,
	search_book_by_author,
	search_book_by_publisher,
	search_book_by_pubdate,
	search_book_by_isbn 
};

char menu_user[] =
"1.���ͼ��\n"
"2.����������\n"
"3.�����߲���\n"
"4.�����������\n"
"5.���������ڲ���\n"
"6.��ISBN����\n"
"7.�˳�\n";

void (*user_func[]) () =
{
	view_book,
	search_book_by_name,
	search_book_by_author,
	search_book_by_publisher,
	search_book_by_pubdate,
	search_book_by_isbn,
	user_exit
 };
 
void show_admin_menu()
{
	int selected = 0;
	while(selected < 1 || selected > MENU_ADMIN_COUNT)
	{
		system("cls");
		printf(menu_title);
		printf(menu_admin);
		printf("������ѡ��Ĳ�����");
		scanf("%d",&selected);
		if(selected < 1 || selected > MENU_ADMIN_COUNT){
			printf("������������������");
			getchar();
			getchar(); 
		}
		else{
			admin_func[selected-1]();
		}
		selected = 0;
	}
 } 
 
void show_search_book_menu()
{
	int s;
	while(s < 1 || s > MENU_SEARCH_BOOK_COUNT)
	{
		system("cls");
		printf(menu_title);
		printf(menu_admin_search_book);
		printf("������ѡ��Ĳ�����");
		scanf("%d",&s);
		if(s == MENU_SEARCH_BOOK_COUNT){
			break;
		}
		if(s < 0 || s > MENU_SEARCH_BOOK_COUNT){
			printf("������������������");
			getchar();
			getchar();
		}
		else{
			admin_search_book_func[s-1]();
		}
		s = 0;
	}
}

void show_user_menu()
{
	int selected = 0;
	while(selected < 1 || selected > MENU_USER_COUNT)
	{
		system("cls");
		printf(menu_title);
		printf(menu_user);
		printf("������ѡ��Ĳ�����");
		scanf("%d", &selected);
		if(selected < 1 || selected > MENU_USER_COUNT)
		{
			printf("�������������");
			getchar();
			getchar();
		}
		else
		{
			user_func[selected - 1] ();
		}
		selected = 0;
	}
}

void admin_exit()
{
	char sure = 'N';
	printf("ȷ��Ҫ�˳��� y or n: ");
	getchar();
	sure = getchar();
	if(sure == 'y')
	{
		save_users_to_file();
		clear_users();
		save_books_to_file();
		clear_books();
		exit(0);
	}
}

void user_exit()
{
	char sure = 'N';
	printf("ȷ��Ҫ�˳��� y or n: ");
	getchar();
	sure = getchar();
	if(sure == 'y')
	{
		clear_users();
		clear_books();
		exit(0);
	}
}

int main()
{
	char input = 'N';
	init_user();
	load_users();
	init_book();
	load_books();
	printf("load...");
	if(login() == ADMIN)
	{
		show_admin_menu();
	}
	else
	{
		show_user_menu();
	}
	return 0;
}
