//
// Created by HP on 2026/4/5.
//
#include <bits/stdc++.h>
using namespace std;
int dfs(int k) {
    if (k == 1) {
        return 1;
    }
    else {
        return dfs(k - 1)*k;
    }
}
int main() {
    int n;
    cin>>n;
    int res = dfs(n);
    cout<<res<<endl;
    return 0;
}
