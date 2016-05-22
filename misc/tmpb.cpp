#include<cstdio>
void print(int n,int k,int m)
{
    if(m<=0)return;
    if(!k)putchar('('),m--;
    else k--;
    for(int i=1;m>0 && i<n;i++)
        if(k<(1<<i))print(i,k,m),m-=(1<<i)-k,k=0;
        else k-=(1<<i);
    if(!k && m>0)putchar(')');
}
main()
{
    int n,k,m;
    while(scanf("%d %d %d",&n,&k,&m)>0 && n+k+m)
        print(n,k,m),puts("");
}
//(()(()))
