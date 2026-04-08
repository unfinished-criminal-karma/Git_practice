//
// Created by HP on 2026/3/4.
// 宽字符版本，支持中文输入（按 ESC 结束）
//
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "database.h"

extern int maxnum;

int main() {
    setlocale(LC_ALL, "");   // 设置区域，使宽字符输入输出正确
    enum character cha = visitor;
    Data *datah = createdata();
    if (datah == NULL) {
        printf("初始化失败，程序退出。\n");
        return 1;
    }
    load_from_file(&datah);
    Data *now_user = NULL;
    int choice = 0;
    int c;

    while (1) {
        if (now_user == NULL) {
            printf("\n\t========== 用户管理系统 ==========\t现在时间：%s\n", get_current_time_str());
            printf("\t1. 登录\n");
            printf("\t2. 注册新用户\n");
            printf("\t3. 退出\n");
            printf("\t请选择操作：");
            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);
            switch (choice) {
                case 1: {
                    now_user = log_in(datah);
                    if (now_user == NULL) {
                        printf("\t登录失败\n");
                        break;
                    }
                    load_words(now_user);
                    cha = now_user->cha;
                    printf("\n");
                    break;
                }
                case 2: {
                    char account[MAXNUM], key[MAXNUM];
                    strcpy(account, "");
                    strcpy(key, "");
                    if (now_user != NULL) {
                        printf("请先退出登录\n");
                        break;
                    }
                    printf("\t请输入新账号：\n");
                    scanf("\t%29s", account);
                    while ((c = getchar()) != '\n' && c != EOF);
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
                    save_to_file(datah);
                    free_list(datah);
                    printf("\t感谢使用，再见！\n");
                    printf("\t按任意键退出...");
                    getch();
                    return 0;
                }
                default: {
                    printf("\t无效选择，请重新输入。\n");
                    printf("\n");
                    break;
                }
            }
        } else {
            printf("\n\t========== 已进入系统 ==========\t现在时间：%s\n", get_current_time_str());
            printf("\t1. 修改密码\n");
            printf("\t2. 注销用户（删除账号）\n");
            printf("\t3. 说点什么\n");
            printf("\t4. 查看随笔\n");
            printf("\t5. 输出所有用户数据（仅限管理员）\n");
            printf("\t6. 清空所有用户数据（仅限管理员）\n");
            printf("\t7. 退出登录\n");
            printf("\t8. 退出\n");
            printf("\t9. 成为manager\n");
            printf("\t请选择操作：");
            scanf("%d", &choice);
            while ((c = getchar()) != '\n' && c != EOF);

            switch (choice) {
                case 1: {
                    if (change(&datah, now_user->account) == 0) {
                        printf("\n");
                        cha = visitor;
                        now_user = NULL;
                    }
                    break;
                }
                case 2: {
                    if (find_user_num(&datah, now_user->account) == -1) {
                        printf("\t账号不存在，注销失败。\n");
                        break;
                    }
                    printf("\t%s\n请确认是否注销，确认按1，返回按0\n", now_user->account);
                    int i = 0;
                    scanf("%d", &i);
                    while ((c = getchar()) != '\n' && c != EOF);
                    if (i == 1) {
                        del(&datah, now_user->num);
                        cha = visitor;
                        now_user = NULL;
                        printf("\t账号已注销。\n");
                        printf("\n");
                    } else if (i == 0) {
                        printf("已取消注销\n");
                        continue;
                    } else {
                        printf("无效输入\n");
                    }
                    break;
                }
                case 3: {   // 说点什么 - 宽字符版本，支持中文
                    printf("\t请输入你想说的话（按 ESC 键结束，支持退格编辑）：\n");
                    wchar_t *input = NULL;
                    size_t capacity = 256;
                    size_t length = 0;
                    input = (wchar_t*)malloc(capacity * sizeof(wchar_t));
                    if (input == NULL) {
                        printf("\t内存不足，无法输入\n");
                        break;
                    }

                    int ch;
                    while (1) {
                        ch = _getwch();
                        if (ch == 27) {   // ESC
                            break;
                        } else if (ch == L'\b' || ch == 127) { // 退格
                            if (length > 0) {
                                length--;
                                wprintf(L"\b \b");
                            }
                        } else if (ch == L'\r') { // 回车换行
                            if (length + 1 >= capacity) {
                                capacity *= 2;
                                input = (wchar_t*)realloc(input, capacity * sizeof(wchar_t));
                                if (!input) break;
                            }
                            input[length++] = L'\n';
                            wprintf(L"\n");
                        } else { // 普通字符（包括中文）
                            if (length + 1 >= capacity) {
                                capacity *= 2;
                                input = (wchar_t*)realloc(input, capacity * sizeof(wchar_t));
                                if (!input) break;
                            }
                            input[length++] = (wchar_t)ch;
                            wprintf(L"%lc", (wchar_t)ch);
                        }
                    }
                    input[length] = L'\0';
                    wprintf(L"\n");

                    if (length > 0 && input[length-1] == L'\n')
                        input[length-1] = L'\0';

                    // 宽字符转多字节（GBK 编码）
                    int mb_len = wcstombs(NULL, input, 0);
                    if (mb_len == -1) {
                        printf("\t转换失败（无效字符）\n");
                        free(input);
                        break;
                    }
                    char *mb_str = (char*)malloc(mb_len + 1);
                    wcstombs(mb_str, input, mb_len + 1);

                    char buffer[2048];
                    const char *time_str = get_current_time_str();
                    snprintf(buffer, sizeof(buffer), "\n[%s]\n%s\n", time_str, mb_str);
                    append_words(now_user, buffer);

                    free(mb_str);
                    free(input);
                    printf("\t已添加到你的随笔中\n");
                    break;
                }
                case 4: {   // 查看随笔
                    if (now_user == NULL || now_user->words == NULL || strlen(now_user->words) == 0) {
                        printf("\t暂无随笔内容，请先使用「说点什么」功能添加。\n");
                    } else {
                        printf("\n\t========== 你的随笔 ==========\n");
                        printf("%s\n", now_user->words);
                        printf("\t========== 结尾 ==========\n");
                    }
                    printf("\n按任意键继续...");
                    getch();
                    break;
                }
                case 5: {
                    if (cha == user || cha == visitor)
                        printf("\t权限不足，无法查看\n");
                    else
                        print_all_users(datah);
                    printf("\n");
                    break;
                }
                case 6: {
                    if (cha == user || cha == visitor)
                        printf("\t权限不足，无法清除\n");
                    else
                        clear_all_users(&datah);
                    printf("\n");
                    break;
                }
                case 7: {
                    cha = visitor;
                    now_user = NULL;
                    break;
                }
                case 8: {
                    save_to_file(datah);
                    free_list(datah);
                    printf("\t感谢使用，再见！\n");
                    printf("\t按任意键退出...");
                    getch();
                    return 0;
                }
                case 9: {
                    printf("\t请输入邀请码：");
                    char welcomekey[MAXNUM];
                    scanf("%s", welcomekey);
                    while ((c = getchar()) != '\n' && c != EOF);
                    if (strcmp(welcomekey, "unfinished_criminal_karma") == 0) {
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