//
// Created by HP on 2026/4/7.
//
#include<iostream>
#include <vector>
#include<cmath>
#include<algorithm>

using namespace std;

int n,res[10010],t = 0;

bool arr[15];

void dfs(const vector<int> &s,const vector<int> &b,int now) {
    if (now == n) {
        int ssum = 1,bsum = 0,flag = 0;
        for (int i = 0; i < n; i++) {
            if (arr[i] == true) {
                flag = 1;
            }
        }
            if (flag) {
                for (int i = 0; i < n; i++) {
            if (arr[i] == true) {
                ssum *= s[i];
                bsum += b[i];
            }
        }
                res[t++] = abs(ssum-bsum);
            }

        return;
    }
            arr[now] = true;
            dfs(s,b,now + 1);
            arr[now] = false;
    dfs(s,b,now + 1);
}

int main() {
    cin>>n;
    vector<int> s(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin>>s[i]>>b[i];
    }
    dfs(s,b,0);
    sort(res,res+t);
    cout<<res[0];
    return 0;
}