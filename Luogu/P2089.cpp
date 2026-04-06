//
// Created by HP on 2026/4/6.
//
#include <bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> res;
int cnt = 0,arr[10];
void dfs(int now) {
    if (now == 10){
        int sum = 0;
        for (int i = 0; i <= 9; i++) {
            sum += arr[i];
        }
        if (sum == n) {
            res.push_back(vector<int> (arr,arr+10));
        }
        return;
    }
    for (int i = 1; i <= 3; i++) {
        arr[now] = i;
        dfs(now + 1);
        arr[now] = 0;
    }
    return;
}
int main() {
    cin >> n;
    if (n < 10 || n > 30) {
        cout << 0 << endl;
        return 0;
    }
    dfs(0);
    cout << res.size() << endl;
    for (auto& re : res) {
        for (int j = 0; j < 10; j++) {
            if (j > 0) cout << " ";
            cout << re[j];
        }
        cout << endl;
    }
}