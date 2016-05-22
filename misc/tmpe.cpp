#include<set>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=10001,M=1000001;
struct pt
{
    int x,y;
    bool operator<(pt a)const{return x<a.x;}
}s[N],t[N];
char name[N][99]={"UNDETERMINED"};
int c[M],h[N];
main()
{
    int i,j,k,n,T;
    set<int> h;
    scanf("%d",&T);
    while(T--)
    {
        h.clear();
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%s",name[i+1]);
            scanf("%d %d",&s[i].x,&t[i].x);
            t[i].x++;
            s[i].y=t[i].y=i+1;
        }
        sort(s,s+n);
        sort(t,t+n);
        for(i=j=k=0;i<M;i++)
        {
            while(j<n && s[j].x==i)h.insert(s[j++].y);
            while(k<n && t[k].x==i)h.erase(t[k++].y);
            if(h.size()==1)c[i]=*h.begin();
            else c[i]=0;
        }
        scanf("%d",&j);
        while(j--)
        {
            scanf("%d",&i);
            puts(name[c[i]]);
        }
    }
}
