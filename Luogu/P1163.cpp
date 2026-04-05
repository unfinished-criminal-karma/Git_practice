//
// Created by HP on 2026/4/5.
//
#include <bits/stdc++.h>
using namespace std;
double w0,w,m;
bool check(double p) {
    double ans = w0;
    for (int i = 1;i <= m;i++) {
        ans = ans * (1+p)-w;
    }
    if (ans > 0 )return true;
    return false;
}
int main() {
    cin>>w0>>w>>m;
    double l = 0.0,r = 3.0;
    double mid;
    while (r-l>1e-8) {
        mid = (l+r)/2.0;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout<<fixed<<setprecision(1)<<mid*100<<endl;
    return 0;
}