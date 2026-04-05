//
// Created by HP on 2026/3/5.
//
// database.h
#ifndef DATABASE_H   // 防止重复包含
#define DATABASE_H
#define MAXNUM 30
#include <time.h>
enum character{user,manager,visitor};

typedef struct Data {
    enum character cha;
    int num;
    char account[MAXNUM];
    char key[MAXNUM];
    char *words;
    struct Data *next;
} Data;

extern int maxnum;   // 声明全局变量（在某个.c文件中定义）

// 函数声明
Data *createdata();
int find_user_num(Data **head, const char *account);
void lastadd(Data **head, const char *account, const char *key);
void lastadd_manager(Data **datah,const char *account,const char *key);
void del(Data **head, int num);
int change(Data **head,const char *account);
void free_list(Data *head);
Data* log_in(Data *datah);
void clear_all_users(Data **head);
const char *trans(enum character cha);
void print_all_users(Data *head);
void save_to_file(Data *head);
void load_from_file(Data **head);
void load_words(Data *user);
const char *get_current_time_str();
void save_words(Data *user,const char *word);

#endif //UNTITLED1_DATABASE_H