#include<cstdio>
#include<cstring>
const int V=1005;
char p[V],c[V][V];
int t;
char go(int v)
{
    if(p[v])return 0;
    if(v==t)return 1;
    p[v]=1;
    for(int i=1;i<=t;i++)
        if(c[v][i]-- && go(i))
            return ++c[i][v];
        else c[v][i]++;
    return 0;
}
int flow()
{
    int i,j=0;
    for(i=0;i<=t;i++)p[i]=0;
    while(go(0))
        for(j++,i=0;i<=t;i++)p[i]=0;
    return j;
}


int abs(int n){return n<0?-n:n;}
struct cab
{
    int time,x1,y1,x2,y2;
    int operator-(cab q){return abs(x2-q.x1)+abs(y2-q.y1);}
    bool operator+(cab q){return q.time-time>(*this-q)+abs(x1-x2)+abs(y1-y2);}
}s[999];
main()
{
    int i,j,k,last,d,n,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        t=n*2+1;
        for(i=0;i<=t;i++)
            memset(c[i],0,sizeof(c[i]));
        for(i=d=0;i<n;i++)
        {
            scanf("%d:%d %d %d %d %d",&j,&k,&s[i].x1,&s[i].y1,&s[i].x2,&s[i].y2);
            s[i].time=j*60+k+d;
            if(s[i].time<last)d+=1440,s[i].time+=1440;
            last=s[i].time;
            c[0][i+1]=1;
            c[i+n+1][t]=1;
        }
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++)
                if(i!=j)
                    c[i+1][j+n+1]=s[i]+s[j];
        printf("%d\n",n-flow());
    }
}
