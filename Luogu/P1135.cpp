#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int ans[205],a,b,dis[205]={0},n;
void dfs(int s,int t)
{
    ans[s]=t;
    //cout<<s<<" "<<t<<endl;
    if(s+dis[s]<=n && t+1<ans[s+dis[s]])
        dfs(s+dis[s],t+1);
    if(s-dis[s]>0  && t+1<ans[s-dis[s]])
        dfs(s-dis[s],t+1);
}
int main()
{
    //freopen("sample.in","r",stdin);
    memset(ans,0x7f,sizeof(ans));
    cin>>n>>a>>b;
    for(int i=1;i<=n;i++)
        cin>>dis[i];
    dfs(a,0);
    if(ans[b]!=0x7f7f7f7f)
        cout<<ans[b];
    else
        cout<<-1;
    return 0;
}
