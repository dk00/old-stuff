#include<cstdio>
#include<algorithm>
using namespace std;
const int N=999;
struct pt{
    int x,y;
    bool operator<(pt a)const
    {
        if(x!=a.x)return x<a.x;
        return y<a.y;
    }
    pt operator-(pt a){return (pt){x-a.x,y-a.y};}
    int operator*(pt a){return x*a.y-a.x*y;}
}s0[N],s1[N],t[N];
int cmp0(pt a,pt b){return (a-s0[0])*(b-s0[0])<0;}
int cmp1(pt a,pt b){return (a-s1[0])*(b-s1[0])<0;}
int go(pt s[],int n)
{
    t[0]=s[0];
    t[1]=s[1];
    int i,j;
    for(i=j=2;i<n;i++){
        while(j>1 && (t[j-1]-t[j-2])*(s[i]-t[j])>=0)j--;
        t[j++]=s[i];
    }
}
main()
{
    int i,j,n,m;
    while(scanf("%d %d",&n,&m)==2 && n+m){
        for(i=0;i<n;i++)
            scanf("%d %d",&s0[i].x,&s0[i].y);
        for(j=0;j<m;j++)
            scanf("%d %d",&s1[i].x,&s1[i].y);
        sort(s0,s0+n);
        sort(s0+1,s0+n,cmp0);
        sort(s1,s1+n);
        sort(s1+1,s1+n,cmp1);
    }
}
