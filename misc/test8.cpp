#include<cstdio>
int s[5][5],v[5],u[7776];
int go(int d)
{
    int i,j,sum=0;
    for(i=j=0;i<5;i++)
        j=j*6+v[i];
    if(u[j])
        return u[j];
    for(i=0;i<5;i++)
    {
        if((i && v[i]>=v[i-1])|| v[i]>=5)
            continue;
        v[i]++;
        sum+=go(d+1);
        v[i]--;
    }
    return(u[j]=sum);
}
char *xd(int n,char *ans)
{
    int i,d,tmp;
    for(d=0;d<25;d++)
        for(i=0;i<5;i++)
        {
            if((i && v[i]+1>v[i-1])|| v[i]>=5)
                continue;
            ans[i*5+v[i]]=d+'A';
            s[i][v[i]++]=d;
            tmp=go(d+1);
            if(tmp>=n)
                break;
            n-=tmp;
            v[i]--;
        }
    return ans;
}
int orz(char *ans)
{
    int i,d,n=1;
    for(d=0;d<25;d++)
        for(i=0;i<5;i++)
        {
            if((i && v[i]+1>v[i-1])|| v[i]>=5)
                continue;
            s[i][v[i]]=d;
            if(d+'A'==ans[i*5+v[i]++])
                break;
            n+=go(d+1);
            v[i]--;
        }
    return n;
}
main()
{
    int n;
    char ans[1000];
    ans[26]=0,u[7775]=1;
    while(scanf("%s",ans)==1)
    {
        for(int i=0;i<5;i++)
            v[i]=0;
        if(ans[0]=='N')
        {
            scanf("%d",&n);
            puts(xd(n,ans));
        }
        else
        {
            scanf("%s",ans);
            printf("%d\n",orz(ans));
        }
    }
}
