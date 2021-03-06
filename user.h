#define MAX_USERNAME 10
#define MAX_PASSWORD 10

//定义用户信息结构体
typedef enum _USER_TYPE{
	ADMIN = 0,
	USER
}USER_TYPE;

typedef struct _user_info
{
	char username[MAX_USERNAME];
	char password[MAX_PASSWORD];
	USER_TYPE  user_type;
}user_info;

//生成链表 
typedef struct _user
{
	user_info ui;
	struct _user *next;
}user;


//函数声明 
void init_user();
void load_users();
USER_TYPE login();
void add_user();
void view_user(); 
void search_user();
void save_users();
void clear_users();

void save_users_to_file();
user *get_last_user();
user *get_previous_user(user *p);
user *find_user(char *name);
void show_user(user_info *info);
void input_user(user_info *info);
void delete_user(user *p);
void update_user(user *p);
