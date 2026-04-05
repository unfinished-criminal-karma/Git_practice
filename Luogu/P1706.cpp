//
// Created by HP on 2026/4/5.
//
#include <bits/stdc++.h>
using namespace std;
#define N 10
int n;
bool st[N];
int arr[N];
void dfs(int x) {
    if (x > n) {
        for (int i = 1; i <= n; i++) {
            cout<<"    "<<arr[i];
        }
        cout<<endl;
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!st[i]) {
            st[i] = true;
            arr[x] = i;
            dfs(x + 1);
            st[i] = false;
            arr[x] = 0;
        }
    }
}
int main() {
    cin>>n;
    dfs(1);
    return 0;
}
