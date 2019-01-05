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
"        图书管理系统          \n\n";

char menu_admin[] = 
"\t1.新增图书\n"
"\t2.浏览图书\n"
"\t3.修改图书\n"
"\t4.查找图书\n"
"\t5.删除图书\n"
"\t6.保存图书\n"
"\t7.新增用户\n"
"\t8.查找用户\n"
"\t9.浏览用户\n"
"\t10.保存用户\n"
"\t11.退出系统\n";

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
"1.书名\n"
"2.作者\n"
"3.出版社\n"
"4.出版日期\n"
"5.ISBN\n"
"6.返回主菜单\n";

void (*admin_search_book_func[]) () =
{
	search_book_by_name,
	search_book_by_author,
	search_book_by_publisher,
	search_book_by_pubdate,
	search_book_by_isbn 
};

char menu_user[] =
"1.浏览图书\n"
"2.按书名查找\n"
"3.按作者查找\n"
"4.按出版社查找\n"
"5.按出版日期查找\n"
"6.按ISBN查找\n"
"7.退出\n";

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
		printf("请输入选择的操作：");
		scanf("%d",&selected);
		if(selected < 1 || selected > MENU_ADMIN_COUNT){
			printf("输入有误，请重新输入");
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
		printf("请输入选择的操作：");
		scanf("%d",&s);
		if(s == MENU_SEARCH_BOOK_COUNT){
			break;
		}
		if(s < 0 || s > MENU_SEARCH_BOOK_COUNT){
			printf("输入有误，请重新输入");
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
		printf("请输入选择的操作：");
		scanf("%d", &selected);
		if(selected < 1 || selected > MENU_USER_COUNT)
		{
			printf("输入错误，请重试");
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
	printf("确认要退出吗 y or n: ");
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
	printf("确认要退出吗 y or n: ");
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
