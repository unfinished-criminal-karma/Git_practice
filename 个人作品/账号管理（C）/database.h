//
// Created by HP on 2026/3/5.
//
// database.h
#ifndef DATABASE_H
#define DATABASE_H

#define MAXNUM 30
#include <time.h>
#include <wchar.h>      // ĞÂÔö¿í×Ö·ûÖ§³Ö
#include <locale.h>     // ÇøÓòÉèÖÃ

enum character { user, manager, visitor };

typedef struct Data {
    enum character cha;
    int num;
    char account[MAXNUM];
    char key[MAXNUM];
    char *words;        // ´æ´¢Ëæ±Ê£¨GBK±àÂë£©
    struct Data *next;
} Data;

extern int maxnum;

Data *createdata();
int find_user_num(Data **head, const char *account);
void lastadd(Data **head, const char *account, const char *key);
void lastadd_manager(Data **datah, const char *account, const char *key);
void del(Data **head, int num);
int change(Data **head, const char *account);
void free_list(Data *head);
Data* log_in(Data *datah);
void clear_all_users(Data **head);
const char *trans(enum character cha);
void print_all_users(Data *head);
void save_to_file(Data *head);
void load_from_file(Data **head);
void load_words(Data *user);
const char *get_current_time_str();
void append_words(Data *user, const char *new_words);

#endif //DATABASE_H