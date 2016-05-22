#include<cstdio>
#include<algorithm>
using namespace std;
const int N=501;
struct ed
{
    int x,y,c;
    bool operator<(ed a)const{return c<a.c;}
}s[N*N];
int p[N],d[N];
int find(int v)
{
    if(v==p[v])return v;
    return p[v]=find(p[v]);
}
void uni(int a,int b)
{
    a=find(a),b=find(b);
    if(d[a]<d[b])p[a]=b;
    else p[b]=a;
    if(d[a]==d[b])d[a]++;
}
int abs(int n){return n<0?-n:n;}
int diff(char a[],char b[])
{
    int i,j=0;
    for(i=0;a[i];i++)
        j+=abs(a[i]-b[i])<?abs(a[i]+10-b[i])<?abs(b[i]+10-a[i]);
    return j;
}
char w[N][5]={"0000"};
main()
{
    int i,j,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        p[0]=d[0]=0;
        for(i=1,m=0;i<=n;i++)
        {
            p[i]=i,d[i]=0;
            scanf("%s",w[i]);
            for(j=0;j<i;j++)
                s[m++]=(ed){i,j,diff(w[i],w[j])};
        }
        sort(s,s+m);
        for(i=j=0;i<m;i++)
            if(find(s[i].x)!=find(s[i].y))
            {
                printf("%d %d %d\n",s[i].x,s[i].y,s[i].c);
                j+=s[i].c;
                uni(s[i].x,s[i].y);
            }
        printf("%d\n",j);
    }
}
