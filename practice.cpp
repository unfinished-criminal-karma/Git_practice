//
// Created by HP on 2026/4/5.
//
#include <bits/stdc++.h>
using namespace std;
int dp(int n) {
    if (n == 1) {
        return 1;
    }
    else {
        return dp(n - 1)*n;
    }
}
int main() {
    int n;
    cin>>n;
    int res = dp(n);
    cout<<res<<endl;
    return 0;
}
