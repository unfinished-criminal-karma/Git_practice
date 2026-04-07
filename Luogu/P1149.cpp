//
// Created by HP on 2026/4/7.
//
#include<bits/stdc++.h>
using namespace std;
int n,cnt = 0;
int arr[4],num[10] = {6,2,5,5,4,5,6,3,7,6};

int trans(int a) {
    if (a == 0)return 6;
    int sum = 0;
    while (a != 0) {
        sum += num[a % 10];
        a/= 10;
    }
    return sum;
}

void dfs(int now) {
    if (now == 3) {
        arr[3] = arr[1]+arr[2];
        if (trans(arr[1])+trans(arr[2])+trans(arr[3]) == n-4) {
            cnt++;
        }
        return;
    }
    for (int i = 0;i <= 2000;i++){
        arr[now] = i;
        dfs(now + 1);
        arr[now] = -1;
    }
}

int main() {
    scanf("%d", &n);
    dfs(1);
    printf("%d", cnt);
    return 0;
}