#include<cstdio>
int getnum()
{
    int i,a;
    char tmp[1000];
    scanf("%s",tmp);
    sscanf(tmp,"%d",&a);
    a*=100;
    for(i=0;tmp[i] && tmp[i]!='.';i++);
    if(tmp[i]=='.')
        if(tmp[i+1])
        {
            a+=(tmp[i+1]-'0')*10;
            if(tmp[i+2])
                a+=tmp[i+2]-'0';
        }
    return a;
}
int go(int n,int s[])
{
    int i,j,k,max=0;
    for(i=0;i<8;i++)
    {
        for(j=k=0;j<3;j++)
            if(i&(1<<j))k+=s[j];
        if(k<=n)max>?=k;
    }
    return max;
}
int s[17000][3];
main()
{
    int i,j,p,q,n,C=1;
    while(scanf("%d",&n) && n)
    {
        for(i=1;i<=n;i++)
            for(j=0;j<3;j++)
                s[i][j]=getnum();
        p=1000000,q=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&j);
            if(p<=0 && j<q)p=-1;
            p=go(p-(j<q),s[j]),q=j;
        }
        printf("Case %d: ",C++);
        if(p>=0)printf("%d.%02d\n",p/100,p%100);
        else puts("No solution");
    }
}
