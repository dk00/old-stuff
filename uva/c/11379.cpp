#include<cstdio>
int n,a,b,s[99];
char path[99];
int count;
void go(int d,int i,int k)
{
    if(!k && i>=n)
    {
        count++;
        path[d]=0;
        puts(path);
        return;
    }
    if(k && (s[k-1]!=a || i>b))
    {
        if(s[k-1]==a)
            path[d]='}';
        else
            path[d]=')';
        go(d+1,i,k-1);
    }
    if(i<n)
    {
        if(i==a)
            path[d]='{';
        else
            path[d]='(';
        s[k]=i;
        go(d+1,i+1,k+1);
    }
}
main()
{
    while(scanf("%d %d %d",&n,&a,&b)==3)
    {
        count=0;
        a--,b--;
        go(0,0,0);
        printf("%d\n",count);
    }
}
