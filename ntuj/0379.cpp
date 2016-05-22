#include<map>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
const int V=99,inf=2000000000;
struct ed
{
    int s,t,c;
    bool operator<(ed a)const{
        if(c!=a.c)return c<a.c;
        return s>a.s;
    }
}s[V*V];
int n,y,d,mini,test,best,p[V],x[V],c[V][V];
int find(int v){return p[v]==v?v:find(p[v]);}
int uni(int a,int b){p[x[d++]=a=find(a)]=b=find(b);}
void undo(){p[x[--d]]=x[d];}
int pp[V];
void go(int m,int i,int d,int sum)
{
    //if(best)return;
    if(d==n-1)
    {
        if(m)best=1;
        mini<?=sum;
        return;
    }
    //if(sum+test*(n-1-d)>=mini)return;
    while(i<y&& (find(s[i].s)==find(s[i].t) ||(!m && !s[i].s)))i++;
    if(i>=y)return;
    uni(s[i].s,s[i].t);
    pp[d]=i;
    go(m-!s[i].s,i+1,d+1,sum+s[i].c);
    undo();
    if(!s[i].s)go(m,i+1,d,sum);
}
main()
{
    int i,j,k,m;
    char tmp[99];
    map<string,int> h;
    while(~scanf("%d",&m))
    {
        best=d=0,h.clear();
        for(i=0;i<V;i++)p[i]=i;
        n=h["Park"]=1;
        for(i=0;i<V;i++)
            for(j=0;j<V;j++)
                c[i][j]=inf;
        while(m--)
        {
            scanf("%s",tmp);
            if(!h[tmp])h[tmp]=++n;
            i=h[tmp]-1;
            scanf("%s",tmp);
            if(!h[tmp])h[tmp]=++n;
            j=h[tmp]-1;
            scanf("%d",&k);
            c[i][j]<?=k;
            c[j][i]=c[i][j];
        }
        for(i=m=0;i<n;i++)
            for(j=i+1;j<n;j++)
                if(c[i][j]<inf)
                    s[m++]=(ed){i,j,c[i][j]};
        sort(s,s+m);
        y=m;
        test=s[m-1].c;
        scanf("%d",&j);
        mini=2000000000,go(j,0,0,0);
        printf("Total miles driven: %d\n",mini);
    }
}
