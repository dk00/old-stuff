#include<map>
#include<vector>
using namespace std;
map<int,map<int,vector<int> > > h;
void ins(int st,int ed,int d,int s=1,int t=N)
{
    printf("%d %d %d %d\n",st,ed,s,t);
    if(st==s && ed==t)
    {
        h[st][ed].push_back(d);
        return;
    }
    int m=(0ll+s+t)/2;
    h[s][t];
    if(st<=m)
        ins(st,ed<?m,d,s,m);
    if(ed>m)
        ins(st>?(m+1),ed,d,(m+1),t);
}
inline char exist(int s,int t){return(h.count(s) && h[s].count(t));}
void print(int s,int t)
{
    if(!exist(s,t))return;
    printf("([%d,%d]:",s,t);
    vector<int>& x=h[s][t];
    for(int i=0;i<x.size();i++)
        printf(" %d",x[i]);
    print(s,(s+t)/2);
    print((s+t)/2+1,t);
    printf(")");
}
