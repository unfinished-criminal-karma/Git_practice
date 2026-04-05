//
// Created by HP on 2026/3/4.
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include"database.h"
#define USER_DATA_FILE "users_data.dat"

int maxnum = 0;

Data *createdata() {//创建哑头节点//
    Data *datah = (Data*)malloc(sizeof(Data));
    if (datah == NULL) {
        return NULL;
    }
    datah->cha = visitor;
    datah->num = -1;
    datah->account[0] = '\0';
    datah->key[0] = '\0';
    datah->words = NULL;
    datah->next = NULL;
    return datah;
}
int find_user_num(Data **datah,const char *account) {
    if (*datah == NULL) {
        return -1;
    }
    Data* temp = *datah;
    if (temp->next != NULL) {
        temp = temp->next;
    }
    else {
        return -1;
    }
    while (temp->next != NULL && strcmp(temp->account,account) != 0) {
        temp = temp->next;
    }
    if (strcmp(temp->account,account) == 0) {
        return temp->num;
    }
    else {
        return -1;
    }
}
void lastadd(Data **datah,const char *account,const char *key) {
    Data* newnode = createdata();
    if(newnode == NULL) {
        return;
    }
    strcpy(newnode->account,account);
    strcpy(newnode->key,key);
    newnode->cha = user;
    newnode->words = NULL;
    Data* datatemp = *datah;
    if (datatemp == NULL) {
        free(newnode);
        return;
    }
    while(datatemp->next != NULL) {
        datatemp = datatemp->next;
    }
    newnode->num = ++maxnum;
    datatemp->next = newnode;
    return;
}
void lastadd_manager(Data **datah,const char *account,const char *key) {
    Data* newnode = createdata();
    if(newnode == NULL) {
        return;
    }
    strcpy(newnode->account,account);
    strcpy(newnode->key,key);
    newnode->words = NULL;
    Data* datatemp = *datah;
    if (datatemp == NULL) {
        free(newnode);
        return;
    }
    while(datatemp->next != NULL) {
        datatemp = datatemp->next;
    }
    newnode->num = ++maxnum;
    datatemp->next = newnode;
    newnode->cha = manager;
    return;
}
void del(Data** datah,int num) {
    if (datah == NULL || *datah == NULL) {
        return;
    }
    Data* tempf = *datah,*temps = *datah;
    while (tempf != NULL && tempf->num != num ) {
        temps = tempf;
        tempf = tempf->next;
    }
    if (tempf == NULL) {
        printf("\t未找到该账号");
        return;
    }
    temps->next = tempf->next;
    temps = temps->next;
    while (temps != NULL) {
        temps->num--;
        temps = temps->next;
    }
    if (tempf->words != NULL) {
        free(tempf->words);
        tempf->words = NULL;
    }
    free(tempf);
    maxnum--;
}
int change(Data **datah,const char *account) {;
    int c = 0;
    Data* temp = *datah;
    if (temp == NULL) {
        printf("\t未找到该账号\n");
        return -1;
    }
    int num = find_user_num(datah, account);
    if (num == -1) {
        printf("\t账号不存在，修改失败。\n");
        return -1;
    }
    while (temp != NULL && temp->num != num) {
        temp = temp->next;
    }
    int count = 3;
    while (count > 0) {
         printf("\t请输入旧密码:\n");
    char key[MAXNUM];
    scanf("%29s",key);
    while ((c = getchar()) != '\n' && c != EOF);
    if (strcmp(key,temp->key) == 0) {
        printf("\t请输入新密码\n");
        scanf("%29s",temp->key);
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\t密码修改成功，请重新登录\n");
        return 0;
    }
    else {
        count--;
        if (count > 0) {
            printf("\t密码错误，请重输，剩余输入次数%d次\n",count);
        }
        else{
            printf("\t修改失败\n");
            return -1;
        }
    }
    }
    return -1;
}
void free_list(Data *head) {
    Data *p = head;
    while (p != NULL) {
        Data *tmp = p;
        p = p->next;
        free(tmp);
    }
}
Data *log_in(Data *datah)
{
    char account[MAXNUM],key[MAXNUM];
    int count = 3;
    while (1) {
        Data *temp_data = datah;
        printf("\t请输入账号\n");
        scanf("%29s",account);
        int order = find_user_num(&temp_data,account);
        if (order != -1) {
            for (int i = 0; i < order; i++) {
                temp_data = temp_data->next;
            }
        }
        else {
            printf("\t登录失败：账号不存在。\n");
            return NULL;

        }
        int c = 0;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\t请选择是否密码可视，输入0为隐藏，输入1为可视\n");
        int t = getchar();
        while ((c = getchar()) != '\n' && c != EOF);
        printf("\t请输入密码:\n");
        if (t == '1') {
            scanf("%29s",key);
            c = 0;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        else {
            int i = 0;
            while (1) {
                char ch = getch();
                if (ch == '\r') {
                    break;
                } else if (ch == '\b' && i > 0) {
                    printf("\b \b");
                    i--;
                } else if (i < MAXNUM - 1) {
                    key[i++] = ch;
                    printf("*");
                }
            }
            key[i] = '\0';
            printf("\n");
        }
        char realkey[MAXNUM];
        strcpy(realkey,temp_data->key);
        int flag = 1;
        if (strcmp(key,realkey) != 0) {
            flag = 0;
        }
        srand((unsigned)time(NULL));
        int random = rand() % 10000;
        reverse:
        printf("\t验证码：%d\n",random);
        printf("\t请输入验证码:\n");
        int temp = 0;
        c = 0;
        scanf("%4d",&temp);
        while ((c = getchar()) != '\n' && c != EOF);
        if (flag == 0) {
            if (count == 0) {
                return NULL;
            }
            printf("\t账号或密码错误，请重新输入,剩余%d次机会\n",count--);
            continue;
        }
        else {
            if(temp != random) {
                printf("\t验证码错误\n");
                goto reverse;
            }
            else {
                if (temp_data->cha == manager) {
                    printf("\t登录成功！\n");
                    printf("\t向您致以亲切的问候,%s\n",trans(temp_data->cha));
                    return temp_data;
                }
                printf("\t登录成功！\n");
                printf("\t向您致以亲切的问候,%s\n",trans(temp_data->cha));
                return temp_data;
            }
        }
    }
}
void clear_all_users(Data **head) {
    if (head == NULL || *head == NULL) return;
    Data *p = (*head)->next;
    while (p != NULL) {
        Data *temp = p;
        p = p->next;
        if (temp->words != NULL) {
            free(temp->words);
        }
        free(temp);
    }
    (*head)->next = NULL;
    maxnum = 0;
    printf("\t数据已全部清除\n");
}
const char *trans(enum character cha) {
        switch (cha) {
            case user: return "user";
            case manager: return "manager";
            default: return "visitor";
        }
    }
void print_all_users(Data *datah) {
    if (datah == NULL || datah->next == NULL) {
        printf("\t暂无用户数据\n");
        return;
    }
    Data *p = datah->next;
    while (p != NULL ) {
        printf("\t%-5d号\t身份:%-10s\t账号：%-31s密码：%-31s\n",p->num,trans(p->cha),p->account,p->key);
        p = p->next;
    }
    printf("\t----已全部输出----\n");
    return;
}
void save_to_file(Data *head) {
    FILE *fp = fopen(USER_DATA_FILE, "w");  // DATA_FILE 定义为 "users.dat"
    if (fp == NULL) {
        printf("警告：无法打开文件保存数据\n");
        return;
    }
    Data *p = head->next; // 跳过哑头节点
    while (p != NULL) {
        // 格式：身份(0=user,1=manager) 账号 密码
        fprintf(fp, "%d %s %s\n", p->cha, p->account, p->key);
        p = p->next;
    }
    fclose(fp);
}
void load_from_file(Data **head) {
    FILE *fp = fopen(USER_DATA_FILE, "r");
    if (fp == NULL) {
        // 首次运行可能没有文件，不报错
        return;
    }
    int ch;
    char account[MAXNUM], key[MAXNUM];
    while (fscanf(fp, "%d %29s %29s", &ch, account, key) == 3) {
        if (ch == 0) { // user
            lastadd(head, account, key);
        } else if (ch == 1) { // manager
            lastadd_manager(head, account, key);
        }
    }
    fclose(fp);
}
const char *get_current_time_str() {// 返回格式 "YYYY-MM-DD HH:MM:SS"
    static char buffer[20];
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}
void append_words(Data *user,const char *new_words) {
    if (user == NULL || new_words == NULL) {
        return;
    }
    char filename[256];
    snprintf(filename,sizeof(filename),"%s.words",user->account);
    FILE *fp ;
    fp = fopen(filename,"a");
    if (fp == NULL) {
        printf("\t无法添加words文件%s\n",filename);
    }
    fprintf(fp,"%s",new_words);
    fclose(fp);
    if (user->words == NULL) {
        uesr->words = malloc(strlen(new_words)+1);
        if (user->words) {
            strcpy(user->words,new_words);
        }
        else {
            size_t old_len = strlen(user->words);
            size_t add_len = strlen(new_words);
            char *new_ptr = realloc(user->words,old_len + add_len + 1);
            if (new_ptr) {
                user->words = new_ptr;
                strcpy(user->words + old_len,new_words);
            }
            else {
                printf("\tt内存不足，无法更新内存中的日记\n");
            }
        }
    }
}
void load_words(Data *user) {
    if (user == NULL) {
        return;
    }
    if (user ->words != NULL) {
        free(user -> words);
        user ->words = NULL;
    }
    char filename[256];
    snprintf(filename,sizeof(filename),"%s.words",user->account);
    FILE *fp = fopen(filename,"r");
    if (fp == NULL) {
        return;
    }
    fseek(fp,0,SEEK_END);
    long size = ftell(fp);
    fseek(fp,0,SEEK_SET);
    if (size <= 0) {
        fclose(fp);
        return;
    }
    user->words = (char*)malloc(size + 1);
    if (user->words == NULL) {
        fclose(fp);
        printf("\t内存不足，无法加载随笔\n");
        return;
    }
    size_t read_size = fread(user->words,1,size,fp);
    user->words[read_size] = '0';
    fclose(fp);
}