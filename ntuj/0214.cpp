#include<cstdio>
#include<cstring>
struct st
{
    int count,len,init,dis;
    bool operator<(st a)
    {
        if(count!=a.count)
            return count<a.count;
        if(len!=a.len)
            return len<a.len;
        if(init!=a.init)
            return init<a.init;
        return dis>a.dis;
    }
};
st test(int i,int d,int n,char p[])
{
    st tmp;
    tmp=(st){0,0,i,d};
    for(;i<n-1 && p[i]=='.';i+=d,tmp.count++);
    if(i>=n-1)
        tmp.len=i-d;
    else
        tmp.len=i;
    return tmp;
}
main()
{
    int i,j,n;
    char tmp[999];
    st t0,best;
    while(scanf("%s",tmp)==1 && strcmp(tmp,"END"))
    {
        for(n=0;tmp[n];n++);
        tmp[n++]='.';
        tmp[n]=0;
        best=(st){-1,-1,-1,2147483647};
        for(i=n-2;i>=0;i--)
            for(j=1;j+1<n;j++)
            {
                t0=test(i,j,n,tmp);
                if(best<t0)
                    best=t0;
            }
        printf("%d %d\n",best.init,best.dis);
        //printf("%d %d\n",best.count,best.len);
    }
}
