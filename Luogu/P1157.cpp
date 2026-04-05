//
// Created by HP on 2026/4/5.
//
#include <bits/stdc++.h>

using namespace std;

int n,r;
vector<int> arr;
vector<bool> st;

void dfs(int n,int r,int i) {
    if (i == r) {
        for (int e : arr) {
            cout<<setw(3)<<e;
        }
        cout<<endl;
        return;
    }
    int start = (i == 0) ? 1:arr[i-1]+1;
    for(int j = start;j <= n;j++){
        if (!st[j]) {
            arr[i] = j;
            st[j] = true;
            dfs(n,r,i+1);
            st[j] = false;
            arr[i] = 0;
        }
    }
    return;
}

int main() {
    cin>>n>>r;
    arr.resize(r);
    st.resize(n + 1, false);
    dfs(n,r,0);
    return 0;
}