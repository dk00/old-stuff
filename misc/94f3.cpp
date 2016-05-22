#include<stdio.h>
int p,s[500][500];
char cc[10000],aa[]="wbg";
int dfs(int x,int y,int n)
{
    if(n<=0)
        return s[x][y];
    n/=2;
    int a,b,c,d;
    d=dfs(x+n,y+n,n);
    c=dfs(x+n,y,n);
    b=dfs(x,y,n);
    a=dfs(x,y+n,n);
    if(a!=2 && a==b && a==c && a==d)
        return a;
    return 2;
}
void print(int x,int y,int n)
{
    if(n<=0)
        return;
    n/=2;
    int a,b,c,d;
    a=dfs(x,y+n,n);
    if(a==2)
    {
        putchar('g');
        print(0,0,n);
    }
    else
        putchar(aa[a]);
    b=dfs(x,y,n);
    if(b==2)
    {
        putchar('g');
        print(0,0,n);
    }
    else
        putchar(aa[b]);
    c=dfs(x+n,y,n);
    if(c==2)
    {
        putchar('g');
        print(0,0,n);
    }
    else
        putchar(aa[c]);
    d=dfs(x+n,y+n,n);
    if(d==2)
    {
        putchar('g');
        print(0,0,n);
    }
    else
        putchar(aa[d]);
}
main()
{
    int i,j,n;
    scanf("%d%c",&n,cc);
    for(i=0;i<n;i++)
    {
        gets(cc);
        for(j=0;j<n;j++)
            if(cc[j]=='0')
                s[i][j]=0;
            else
                s[i][j]=1;
    }
    p=0;
    i=dfs(0,0,n);
    if(i==2)
    {
        putchar('g');
        print(0,0,n);
    }
    else
        putchar(aa[i]);
    puts("");
    scanf(" ");
}
