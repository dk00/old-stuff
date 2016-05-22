#include<cstdio>

char test(char a[],char b[])
{
    int i,j;
    for(i=j=0;a[i];i++)
    {
        for(;b[j];j++)
            if(a[i]==b[j])break;
        if(!b[j++])return 1;
    }
    return 0;
}
int n,max;
char path[20],s[101][20];
void go(int d,int l)
{
    if(!s[0][d])
    {
        path[l]=0;
        for(d=1;d<n;d++)
            if(test(path,s[d]))return;
        max>?=l;
        return;
    }
    path[l]=s[0][d];
    go(d+1,l+1);
    go(d+1,l);
}
main()
{
    int i;
    while(scanf("%d",&n)==1)
    {
        gets(s[0]);
        for(i=0;i<n;i++)
            gets(s[i]);
        max=0;
        go(0,0);
        printf("%d\n",max);
    }
}
