//
// Created by HP on 2026/4/6.
//
#include <bits/stdc++.h>
using namespace std;
int N,M,re = 0;
int arr[10010];
int res[10010];
bool st[10010];
void dfs(int now) {
    if (now == N) {
        re++;
        if (re == M+1) {
            for (int e = 0;e < N;e++ ) {
                cout<<res[e]<<" ";
            }
            exit(0);
        }
        return;
    }
    for (int i = 0;i < N;i++) {
        if (!re) {
            i = arr[now]-1;
        }
        if (!st[i]) {
            st[i] = true;
            res[now] = i+1;
            dfs(now+1);
            st[i] = false;
            res[now] = 0;
        }

    }
    return;
}
int main() {
    cin>>N;
    cin>>M;
   for (int i = 0;i < N;i++) {
       cin>>arr[i];
    }
    dfs(0);
    return 0;


}