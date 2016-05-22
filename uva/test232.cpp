#include<cstdio>
int s[100][100];
int k;
int go(int a,int b)
{
    if(a==k+2 && b==k*k+4*k+4)
    {
        a++,a--;
    }
    if(s[a][b])return s[a][b]-1;
    if(a>b)
        return go(b,a);
    s[a][b]=1;
    if(b-a<=k)s[a][b]=2;
    int i,j;
    for(i=1;i<=a;i++)
        if(!go(a-i,b))s[a][b]=2;
    for(i=1;i<=b;i++)
        if(!go(a,b-i))s[a][b]=2;
    for(i=1;i<=a;i++)
        for(j=(i-k)>?1;j<=i+k && j<=b;j++)
            if(!go(a-i,b-j))s[a][b]=2;
    return s[a][b]-1;
}
main()
{
    int i,j;
    while(scanf("%d",&k))
    {
        for(i=0;i<70;i++)
            for(j=0;j<70;j++)
                s[i][j]=0;
        s[0][0]=1;
        for(i=0;i<70;i++)
        {
            for(j=0;j<70;j++)
                printf("%d",go(i,j));
            puts("");
        }
    }
}
