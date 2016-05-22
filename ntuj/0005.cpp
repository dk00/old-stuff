#include<cstdio>
int x[20][20];
char test(char a[],char b[])
{
    int i,j;
    for(i=1;a[i];i++)
        for(j=1;b[j];j++)
            if(a[i]==b[j])
                x[i][j]=x[i-1][j-1]+1;
            else
                x[i][j]=x[i-1][j]>?x[i][j-1];
    return x[i-1][j-1]!=i-1;
}
int n,max;
char s[999][99],path[99];
void go(int d,int m)
{
    if(!s[0][d])
    {
        path[m]=0;
        for(d=1;d<n;d++)
            if(test(path-1,s[d]-1))return;
        max>?=m;
        return;
    }
    path[m]=s[0][d];
    go(d+1,m+1);
    go(d+1,m);
}

main()
{
    int i;
    while(scanf("%d",&n)>0)
    {
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
        max=0;
        go(0,0);
        printf("%d\n",max);
    }
}
