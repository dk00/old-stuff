#include<cstdio>
char s[99];
long long s1[99][99],s2[99][99];
long long calc2(int x,int y)
{
    if(x==y)return(s[x]==s[y]);
    if(s[x]!=s[y])return 0;
    if(s2[x][y])
        return(s2[x][y]>?0);
    int i,j;
    s2[x][y]=1;
    for(i=x+1;i<y;i++)
        for(j=i;j<y;j++)
            if(s[i]==s[x])
                s2[x][y]+=calc2(i,j);
    if(!s2[x][y])s2[x][y]=0;
    return(s2[x][y]>?0);
}
long long calc1(int x,int y)
{
    if(x==y || s[x]!=s[y])return 0;
    if(s1[x][y])
        return(s1[x][y]>?0);
    int i,j;
    for(i=x+1;i<y;i++)
        for(j=i;j<y;j++)
        {
            s1[x][y]+=calc1(i,j);
            if(s[i]!=s[x])
                s1[x][y]+=calc2(i,j);
        }
    if(!s1[x][y])s1[x][y]=-1;
    return(s1[x][y]>?0);
}
main()
{
    int i,j,t;
    long long sum;
    scanf("%d",&t);
    gets(s);
    while(t--)
    {
        gets(s);
        for(i=0;s[i];i++)
            for(j=i;s[j];j++)
                s1[i][j]=s2[i][j]=0;
        for(i=sum=0;s[i];i++)
            for(j=i;s[j];j++)
                sum+=calc1(i,j)+calc2(i,j);
        printf("%lld\n",sum);
    }
}
