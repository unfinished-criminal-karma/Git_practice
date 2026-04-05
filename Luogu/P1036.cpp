//
// Created by HP on 2026/4/5.
//
#include <bits/stdc++.h>

using namespace std;

int cnt = 0,n,k;

int x[21];
int arr[21];

bool is_prime(int sum) {
    if (sum < 2)
        return false;
    for (int i = 2; i <= sum/i; i++) {
        if (sum % i == 0) {
            return false;
        }
    }
    return true;
}

void dfs(int start,int j) {
    if (j == k) {
        long long sum = 0;
        for (int i = 0; i < k; i++) {
            sum += arr[i];
        }
        if (is_prime(sum)) {
            cnt++;
        }
        return;
    }
    for (int i = start; i < n; i++) {
            arr[j] = x[i];
            dfs(i+1,j+1);
            arr[j] = 0;
    }
}

int main() {
    cin >> n >> k ;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    dfs(0,0);
    cout << cnt;
    return 0;
}
