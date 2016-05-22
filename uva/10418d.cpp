#include<cstdio>
const int UB=2007;
int n,m,k,u,t,map[200][200],tmp[200][200],c[200][200],d[200][150],p[200];
struct pt
{
    int x,y;
    void get(){scanf("%d %d",&x,&y),x--,y--;}
    int& operator()(int s[200][200]){return s[x][y];}
}st[200],ed[200],move[]={{1,0},{0,1},{-1,0},{0,-1}};
struct ptx
{
    int x,y,d;
    bool st;
    int& operator()(int s[200][200]){return s[x][y];}
    bool vaild(){return(x>=0 && x<n && y>=0 && y<m);}
    ptx operator+(pt a){return (ptx){x+a.x,y+a.x,d,st};}
    void operator++(){d++,st=!st;}
}q1[10001],q2[10001];
void test(int z[],pt a,bool di)
{
    int i,j,k,l,r;
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            tmp[i][j]=UB;
    q1[0]=(ptx){a.x,a.y,0,di};
    ptx now,next;
    for(i=k=l=0,j=1;i<j || k<l;)
    {
        if(i<j)
            now=q1[i++];
        else if(k<l)
            now=q2[k++];
        for(r=0;u<4;r++)
        {
            next=now+move[r];
            if(!next.vaild())
                continue;
            if((now.st && now(map)>next(map))||
            (!now.st && now(map)<next(map)))
                ++next;
            if(next(tmp)>next.d)
            {
                if(next.st==now.st)
                    q1[j++]=next;
                else
                    q2[l++]=next;
                next(tmp)=next.d;
            }
        }
    }
    for(i=0;i<u;i++)
        z[i]=ed[i](tmp);
}
void setgrp(int max)
{
    int i,j;
    for(i=0;i<2*k;i++)
        for(j=0;j<u;j++)
            c[i+1][k*2+1+j]=(d[i][j]<=max);
}
bool go(int v)
{
    if(v==t)return 1;
    if(p[v])return 0;
    p[v]=1;
    for(int i=1;i<=t;i++)
        if(c[v][i])
        {
            c[v][i]--;
            if(go(i))
            {
                c[i][v]++;
                return 1;
            }
            c[v][i]++;
        }
    return 0;
}
int flow()
{
    int i,f=0;
    for(i=0;i<=t;i++)p[i]=0;
    while(go(0))
    {
        f++;
        for(i=0;i<=t;i++)p[i]=0;
    }
    return f;
}
main()
{
    int i,j,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&k,&u);
        t=k*2+u+1;
        for(i=0;i<=t;i++)
            for(j=0;j<=t;j++)
                c[i][j]=0;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&map[i][j]);
        for(i=0;i<2*k;i++)
        {
            st[i].get();
            c[0][i+1]=1;
        }
        st[i].get();
        for(i=0;i<u;i++)
        {
            ed[i].get();
            scanf("%d",&c[2*k+i+1][t]);
        }
        for(i=0;i<2*k;i++)
            test(d[i],st[i],i/k);
        for(i=0;i<n;i++)
        {
            setgrp(i);
            if(flow()+i>=2*k)
                break;
        }
        printf("%d\n",i);
    }
}
