#include<cstdio>
int n;
char s[102][200];
int p[102][200];
void go(int j,int d)
{
    if(j)
    {
        go(j-1,p[j][d]);
        putchar(s[j][d]/2+'0');
    }
}
main()
{
    int i,j;
    while(scanf("%d",&n) && n)
    {
        for(j=0;j<=100;j++)
            for(i=0;i<n;i++)
                s[j][i]=0;
        s[1][1%n]=3;
        for(j=1;!s[j][0] && j<=100;j++)
            for(i=0;i<n;i++)
                if(s[j][i])
                {
                    s[j+1][(i*10+1)%n]=3;
                    p[j+1][(i*10+1)%n]=i;
                    s[j+1][(i*10)%n]=1;
                    p[j+1][(i*10)%n]=i;
                }
        go(j,0);
        puts("");
    }
}
