//
// Created by HP on 2026/3/4.
//
#include<stdio.h>
#include <stdlib.h>
#include<conio.h>
#include <string.h>
#include"database.h"
// 声明全局变量 maxnum（已在 database.c 中定义）
extern int maxnum;
int main() {
    enum character cha = visitor;
    Data *datah = createdata();// 创建哑头节点
    if (datah == NULL) {
        printf("初始化失败，程序退出。\n");
        return 1;
    }
    load_from_file(&datah);
    Data *now_user = NULL;
    int choice = 0;
    int c;  // 用于清空缓冲区

    while (1) {
        if (now_user == NULL) {
            printf("\n\t========== 用户管理系统 ==========\t现在时间：%s\n",get_current_time_str());
            printf("\t1. 登录\n");
            printf("\t2. 注册新用户\n");
            printf("\t3.退出\n");
            printf("\t请选择操作：");
            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);// 清空输入缓冲区，去除残留的换行符
            switch (choice) {
                case 1:  // 登录
                {
                    now_user = log_in(datah);
                    if (now_user == NULL) {
                        printf("\t登录失败\n");
                        break;
                    }
                    cha = now_user->cha;
                    printf("\n");
                    break;
                }

                case 2:  // 注册
                {
                    char account[MAXNUM], key[MAXNUM];
                    strcpy(account,"");
                    strcpy(key,"");
                    if (now_user != NULL) {
                        printf("请先退出登录\n");
                        break;
                    }
                    printf("\t请输入新账号：\n");
                    scanf("%29s", account);
                    while ((c = getchar()) != '\n' && c != EOF);

                    // 检查账号是否已存在
                    int num = find_user_num(&datah, account);
                    if (num != -1) {
                        printf("\t账号已存在，注册失败。\n");
                        break;
                    }
                    printf("\t请输入密码：\n");
                    scanf("%29s", key);
                    while ((c = getchar()) != '\n' && c != EOF);
                    lastadd(&datah, account, key);
                    printf("\t注册成功,欢迎成为我们的一员\n");
                    printf("\n");
                    break;
                }

                case 3: {
                    save_to_file(datah);   // 保存数据到文件
                    free_list(datah);      // 释放内存（可选）
                    printf("\t感谢使用，再见！\n");
                    printf("\t按任意键退出...");
                    getch();          // 等待用户按键
                    return 0;
                }


                default: {
                    printf("\t无效选择，请重新输入。\n");
                    printf("\n");
                    break;
                }

            }

        }
        else {
            printf("\n\t========== 已进入系统 ==========\t现在时间：%s\n",get_current_time_str());
            printf("\t1. 修改密码\n");
            printf("\t2. 注销用户（删除账号）\n");
            printf("\t3. 说点什么\n");
            printf("\t4. 改点什么\n");
            printf("\t5.输出所有用户数据（仅限管理员）\n");
            printf("\t6.清空所有用户数据（仅限管理员）\n");
            printf("\t7. 退出登录\n");
            printf("\t8.退出\n");
            printf("\t9.成为manager\n");
            printf("\t请选择操作：");
            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);// 清空输入缓冲区，去除残留的换行符

            switch (choice) {

                case 1:  // 修改密码
            {
                // 调用修改密码函数（注意：该函数内部会处理旧密码验证）
                if (change(&datah,now_user->account) == 0) {
                    printf("\n");
                    cha = visitor;
                    now_user = NULL;
                }
                break;
            }

                case 2:  // 注销（删除账号）
            {
                if (find_user_num(&datah,now_user->account) == -1) {
                    printf("\t账号不存在，注销失败。\n");
                    break;
                }
                printf("\t%s\n请确认是否注销，确认按1，返回按0\n",now_user->account);
                int i = 0;
                scanf("%d", &i);
                while ((c = getchar()) != '\n' && c != EOF);
                if (i == 1) {
                    del(&datah, now_user->num);
                    cha = visitor;
                printf("\t账号已注销。\n");
                printf("\n");
                }
                else if (i == 0) {
                    printf("已取消注销\n");
                    continue;
                }
                else {
                    printf("无效输入\n");
                }
                break;
            }

                case 3: {

                }

                case 4: {
                    printf("骗你的，说出去的话犹如泼出去的水，每个字都是你的投影，不是吗？\n");
                    continue;
                }

                case 5: //输出所有用户数据
            {
                if (cha == user || cha == visitor) {
                    printf("\t权限不足，无法查看\n");
                }
                else {
                    print_all_users(datah);
                }
                printf("\n");
                break;
            }

                case 6: //清空所有用户数据
            {
                if (cha == user || cha == visitor) {
                printf("\t权限不足，无法清除\n");
                }
                else {
                clear_all_users(&datah);
            }
                printf("\n");
                break;
            }

                case 7:
            {
                cha = visitor;
                now_user = NULL;
                break;
            }

                case 8: { // 退出
                save_to_file(datah);   // 保存数据到文件
                free_list(datah);      // 释放内存（可选）
                printf("\t感谢使用，再见！\n");
                printf("\t按任意键退出...");
                getch();          // 等待用户按键
                return 0;
            }

                case 9: {
                printf("\t请输入邀请码：");
                char welcomekey[MAXNUM];
                scanf("%s", welcomekey);
                while ((c = getchar()) != '\n' && c != EOF);
                int com = strcmp(welcomekey, "unfinished_criminal_karma");
                if (com == 0) {
                        now_user->cha = manager;
                        cha = manager;
                        printf("\r恭喜你成为我们的新管理员!\n");
                        printf("\n");
                }
                break;
            }

                default: {
                printf("\t无效选择，请重新输入。\n");
                printf("\n");
                break;
            }
            }
        }
    }
}