#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"book.h"
#include"management.h"
#include"user.h"

#define BOOK_FILE "book.dat"

book *first_book = NULL;//结构体链表头节点

void add_book()
{
	char try_again = 'y';
	book *p = NULL;
	book *new_book = NULL;
	while(try_again == 'y')
	{
		new_book = (book *)malloc(sizeof(book));//创建一个new_book *
		memset(new_book, 0, sizeof(book));//初始化
		new_book->next = NULL;
		printf("增加图书...\n");
		input_book(&(new_book->bi));//使用input_book给其赋值
		p = get_last_book();//获取最后一个节点 
		if(p == NULL){
		    first_book = new_book;//赋值给头节点 
    	}
    	else{
    		p->next = new_book;//放到最后 
		} 
		printf("是否继续添加 y or n :");
		getchar();
		try_again = getchar();
	}
 } 
 
void view_book()
{
	book *p = NULL;
	char input = 'y';
	int c = 0;
	while(input == 'y')
	{
		c = 0;
		p = first_book;
		printf("        书名        |        作者        |\n");
		printf("------------------------------------------\n");
		while(p != NULL)
		{
			printf("%20s|%20s",p->bi.book_name,p->bi.author);
			printf("\n------------------------------------------\n");
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

void search_book_by_name()
{
	book *p = NULL;
	char s[MAX_BOOK_NAME] = {0};
	char input = 'y';
	int count = 0;
	int i = 0;
	printf("load...\n");
	while(input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s, 0, MAX_BOOK_NAME);//clear
		printf("请输入书名：");
		scanf("%s", s);
		while(p != NULL)
		{
			if(findstr(p->bi.book_name, s) != -1){
				show_book(&(p->bi));
				count++;
			}
			p = p->next;
		}
		if(count == 0){
			printf("未查询到图书信息，是否继续查找 y or n:");
			getchar();
			input = getchar();
			continue;
		}
		printf("是否继续查找 y or n:");
		getchar();
		input = getchar();
	}
}

void search_book_by_author()
{
	book *p = NULL;
	char s[MAX_AUTHOR] = {0};
	char input = 'y';
	int count = 0;
	int i = 0;
	printf("load...\n");
	while(input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s, 0, MAX_AUTHOR);//clear
		printf("请输入作者：");
		scanf("%s", s);
		while(p != NULL)
		{
			if(findstr(p->bi.author, s) != -1){
				show_book(&(p->bi));
				count++;
			}
			p = p->next;
		}
		if(count == 0){
			printf("未查询到图书信息，是否继续查找 y or n:");
			getchar();
			input = getchar();
			continue;
		}
		printf("是否继续查找 y or n:");
		getchar();
		input = getchar();
	}
}

void search_book_by_publisher()
{
	book *p = NULL;
	char s[MAX_PUBLISHER] = {0};
	char input = 'y';
	int count = 0;
	int i = 0;
	printf("load...\n");
	while(input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s, 0, MAX_PUBLISHER);//clear
		printf("请输入出版社：");
		scanf("%s", s);
		while(p != NULL)
		{
			if(findstr(p->bi.publisher, s) != -1){
				show_book(&(p->bi));
				count++;
			}
			p = p->next;
		}
		if(count == 0){
			printf("未查询到图书信息，是否继续查找 y or n:");
			getchar();
			input = getchar();
			continue;
		}
		printf("是否继续查找 y or n:");
		getchar();
		input = getchar();
	}
}

void search_book_by_pubdate()
{
	book *p = NULL;
	char s[MAX_DATE] = {0};
	char input = 'y';
	int count = 0;
	int i = 0;
	printf("load...\n");
	while(input == 'y')
	{
		count = 0;
		p = first_book;
		memset(s, 0, MAX_DATE);//clear
		printf("请输入出日期：");
		scanf("%s", s);
		while(p != NULL)
		{
			if(findstr(p->bi.pub_date, s) != -1){
				show_book(&(p->bi));
				count++;
			}
			p = p->next;
		}
		if(count == 0){
			printf("未查询到图书信息，是否继续查找 y or n:");
			getchar();
			input = getchar();
			continue;
		}
		printf("是否继续查找 y or n:");
		getchar();
		input = getchar();
	}
}

void search_book_by_isbn()
{
	book *p = NULL;
	book *result = NULL;
	char s[MAX_ISBN] = {0};
	char input = 'y';
	
	while(input == 'y')
	{
		printf("load...\n");
		printf("请输入ISBN：");
		scanf("%s", s);
		p = first_book;
		result = NULL;
		while(p != NULL)
		{
			if(strcmp(p->bi.ISBN,s) == 0){
				result = p;
				break;
			}
			p = p->next;
		}
		if(result != NULL){
			printf("success");
			show_book(&(result->bi));
		}
		else{
			printf("未查询到图书信息");
		}
		printf("是否继续查找 y or n:");
    	getchar();
    	input = getchar();
	}
}

//删除图书 
void delete_book()
{
	char input = 'y';
	int i = 0; 
	char isbn[MAX_ISBN] = {0};
	book *p = NULL;
	book *result = NULL;
	while(input == 'y')
	{
		printf("load...\n");
		printf("请输入ISBN：");
		scanf("%s", isbn);
		p = first_book;
		result = NULL;
		while(p != 0)
		{
			if(strcmp(p->bi.ISBN, isbn) == 0){
				result = p;
				i++;
				break;
			}
			p = p->next;
		}
		if(result != NULL){
			show_book(&(p->bi));
			printf("确认删除 y or n :");
			getchar();
			input = getchar();
			if(input == 'y'){
				if(i == 1){
					result = first_book->next;
					free(&(first_book->bi));
					first_book = result;
				}
				if(i != 1){
					get_previous_book(p)->next = p->next;
	    			free(p);
				}	
			}
		}
		else{
			printf("未查找到图书");
		}
		printf("是否要删除其他图书 y or n:");
		getchar();
		input = getchar();
	}
}

void save_books()
{
	printf("load...\n");
	save_books_to_file();
	printf("success");
	getchar();
	getchar(); 
}

//保存图书信息到文件 
void save_books_to_file()
{
	FILE *fp = fopen(BOOK_FILE, "wb");
	book *p = first_book;
	while(p != NULL)
	{
		fwrite(&(p->bi),sizeof(book_info), 1, fp);
		fseek(fp, 0, SEEK_END);
		p = p->next;
	}
	fclose(fp);
}

//图书信息初始化 
void init_book()
{
	FILE *fp = NULL;
	FILE *fps = NULL;
	fp = fopen(BOOK_FILE, "r");
	if(fp == NULL){
		fps = (BOOK_FILE, "w");//创建文件
		if(fp == NULL){
			printf("file creation failed");
			getchar();
			exit(0);
		} 
	}
	fclose(fp);
	fclose(fps);
}

//加载图书信息 
void load_books()
{
	book *b = NULL;
	book *last = NULL;
	FILE *fp = NULL;
	int c = 0;
	b = (book*)malloc(sizeof(book));
	memset(b, 0, sizeof(book));//初始化
	b->next = NULL;
	fp = fopen(BOOK_FILE, "rb");
	while(fread(&(b->bi), sizeof(book_info), 1, fp) == 1)
	{
		if(first_book == NULL){
			first_book = b;//头节点 
		}
		else{
			last = get_last_book();//链表最后
			last->next = b; 
	    } 
	    c++;
	    fseek(fp, c *sizeof(book_info), SEEK_SET);//文本指针 加一 
	    b = (book*)malloc(sizeof(book));
		memset(b, 0, sizeof(book));
		b->next = NULL;
    }
    free(b);
    b = NULL;
    fclose(fp);
} 

//清除图书信息 
void clear_books()
{
	book *p = NULL;
	while(first_book != NULL)
	{
		if(first_book->next != NULL){
			p = first_book;
			first_book = first_book->next;
			free(p);
			p = NULL;
		}
		else{
			free(first_book);
			first_book = NULL;
		}
	}
}

//模糊查找功能的实现 
int findstr(char *source, char *str)
{
	int pos = -1;
	int i = 0;
	int j = 0;
	int m = strlen(source);
	int n = strlen(str);
	
	/*匹配字符*/ 
	if(m == 0 || n == 0  || m < n){
		return pos;
	}
	if(m == n){
		if(strcmp(source, str) == 0){
			return 0;
		}
		else{
			return -1;
		}
	}
	for(i = 0 ; i < ( m - n ); i++)
	{
		pos = i;
		for(j = 0 ; j < n ; j++)
		{
			if(source[i+j] != str[j]){
				pos = -1;
				break;
			}
		}
		if(pos != -1){
			break;
		}
	}
	return pos;
}

book *get_last_book()
{
	book *p = first_book;
	if(p == NULL)
	{
		return p;
	}
	while((p != NULL) && (p->next != NULL))
	{
		p = p->next;
	}
	return p;
 } 
 
 void input_book(book_info *info)
 {
 	printf("请输入书名：");
	scanf("%s", info->book_name); 
	printf("请输如入作者：");
	scanf("%s", info->author);
	printf("请输入出版社：");
	scanf("%s", info->publisher);
	printf("请输入出版日期：");
	scanf("%s", info->pub_date);
	printf("请输 ISBN：");
	scanf("%s", info->ISBN);
	printf("请输入页数：");
	scanf("%d",&info->pages);
 }
 
 void show_book(book_info *info)
 {
 	printf("--------------------------------\n");
	printf("书名：%20s\n", info->book_name); 
	printf("作者：%20s\n", info->author);
	printf("出版社：%18s\n", info->publisher);
	printf("出版日期：%16s\n", info->pub_date);
	printf("ISBN：%20s\n", info->ISBN);
	printf("页数：%20d\n", info->pages);
	printf("\n");      
 }
 
 //更新图书信息 
 void update_book()
{
	char input = 'y';
	book *p = NULL;
	book *result = NULL;
	char exist_b[20] = {0};
	book *update_b = NULL;
	book_info *new_b = (book_info*)malloc(sizeof(book_info));
	memset(new_b, 0, sizeof(book_info));
	while(input == 'y')
	{
		printf("load...\n");
		printf("请输入要修改的书籍的ISBN：\n");
    	scanf("%s", exist_b);
		p = first_book;
		result = NULL;
		
		/*查询目标图书地址*/ 
		while(p != NULL)
		{
			if(strcmp(p->bi.ISBN,exist_b) == 0){
				result = p;
				break;
			}
			p = p->next;
		}
		if(result != NULL){
			printf("success\n");
			update_b = result;
			
			/*修改信息*/ 
			input_book(new_b);
     		strcpy(update_b->bi.book_name, new_b->book_name);
        	strcpy(update_b->bi.author, new_b->author);
        	strcpy(update_b->bi.publisher, new_b->publisher);
    		strcpy(update_b->bi.pub_date, new_b->pub_date);
        	strcpy(update_b->bi.ISBN, new_b->ISBN);
        	update_b->bi.pages = new_b->pages;
        	printf("修改成功\n");
		}
		else{
			printf("未查询到图书信息，不能修改");
		}
		printf("是否继续查找 y or n:");
    	getchar();
    	input = getchar();
	}
	free(new_b);
 } 
 
 book *get_previous_book(book *p)
 {
 	book *previous = first_book;
 	while(previous != NULL)
 	{
 		if(previous->next == p){
 			break;
		 }
		 previous = previous->next;
	 }
	 return previous;
 }
 
