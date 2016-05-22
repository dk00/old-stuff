#include<cstdio>
#include<algorithm>
int w,m,sum,num,max,best,s[10000];
void take(int i){num++,s[i]=-s[i];}
void put(int i){num--,s[i]=-s[i];}
bool go(int u,int rw,int i)
{
    max>?=num;
    if(max==best)return 1;
    if(u<=0)return 0;
    int j;
    if(rw==w)
    {
        for(i=j=sum=0;i<m;i++)
        {
            if(s[i]<=0)continue;
            if(s[i]+sum>u*w)break;
            j++,sum+=s[i];
        }
        if(j+num<=max)return 0;
        for(i=0;s[i]<=0;i++);
        take(i);
        go(u,rw+s[i],i+1);
        put(i);
        return 0;
    }
    for(;s[i]>rw && i<m;i++);
    if(s[i]==rw || i>=m)
    {
        if(i<m)take(i);
        go(u-1,rw,0);
        if(i<m)put(i);
        return 0;
    }
    for(;i<m;i++)
        if(s[i]>0)
        {
            take(i);
            j=go(u,rw+s[i],i+1);
            put(i);
            if(j)return 1;
        }
    return 0;
}
bool cmp(int a,int b){return a>b;}
main()
{
    int i,j,n;
    scanf("%d %d %d",&n,&w,&m);
    sum=n*w;
    for(i=0;i<m;i++)
    {
        scanf("%d",&s[i]);
        if(s[i]>w)i--,m--;
        else sum-=s[i];
    }
    std::sort(s,m+s,cmp);
    while(sum<0)sum+=s[--m];
    best=m,num=max=0;
    go(n,w,0);
    printf("%d\n",max);
    scanf(" ");
}
