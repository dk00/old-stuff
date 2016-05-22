#include<cstdio>
#include<cstring>
const int V=1024,inf=2147483647;
int t,c[V][V],p[V],d[V],u[V*10],q[V*10];
int sp()
{
    int i,j,k;
    for(i=0;i<=t;i++)
        d[i]=inf;
    d[q[0]=t]=0;
    for(i=0,j=1;d[0]>=inf && i<j;i++)
        for(k=0;k<=t;k++)
            if(c[k][q[i]] && d[k]>=inf)
                d[q[j++]=k]=d[q[i]]+1;
    return d[0];
}
int go(int v)
{
    if(v==t)return 1;
    int sum=0;
    for(;u[v]<=t;u[v]++)
        if(d[v]==d[u[v]]+1)
        {
            if(c[v][u[v]]-- && go(u[v]))
            {
                c[u[v]][v]++;
                if(v)return 1;
                sum++;
            }
            else c[v][u[v]]++;
        }
    //if(!v)printf("%d/",sum);
    return sum;
}
int flow()
{
    int i,sum=0;
    while(sp()<inf)
    {
        for(i=0;i<=t;i++)u[i]=0;
        sum+=go(0);
    }
    //puts("");
    return sum;
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
