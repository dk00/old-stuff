#include<cstdio>
int getnum()
{
    int a,b;
    scanf("%d.%d",&a,&b);
    return a*10000+b;
}
int c[101];
int C(int st,int ed)
{
    if(st)return c[ed]-c[st-1];
    return c[ed];
}
int n,p[101][101];
long long s[101][101];
long long go(int a,int b)
{
    if(p[a][b])return s[a][b];
    long long tmp;
    for(int i=a+1;i<=b;i++)
    {
        tmp=go(a,i-1)+go(i,b)+C(a,b);
        if(!p[a][b] || tmp<s[a][b])
            s[a][b]=tmp,p[a][b]=i;
    }
    return s[a][b];
}
char path[103];
void print(int a,int b,int d=0)
{
    if(a==b)
    {
        path[d]=0;
        puts(path);
        return;
    }
    path[d]='0';
    print(a,p[a][b]-1,d+1);
    path[d]='1';
    print(p[a][b],b,d+1);
}
main()
{
    long long i,j,C=0;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
        {
            c[i]=getnum();
            for(j=0;j<n;j++)
                p[i][j]=0;
        }
        for(i=1;i<n;i++)
            c[i]+=c[i-1];
        i=go(0,n-1);
        if(C++)puts("");
        printf("%.4lf\n",i/10000.0);
        print(0,n-1);
    }
}
