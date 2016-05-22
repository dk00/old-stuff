#include<cstdio>
#include<cstring>
#include<cstdlib>
bool notp[302];
int p,d,path[15],pr[500],s[15][1001];
int prcmp(const void *a,const void *b)
{
    char tmp1[4],tmp2[4];
    sprintf(tmp1,"%d",*(int *)a);
    sprintf(tmp2,"%d",*(int *)b);
    return strcmp(tmp1,tmp2);
}
int go(int n,int k,int i)
{
    if((n==0 && k) || k<0 || !s[k][n])
        return 0;
    if(n==0 && k==0)
    {
        if(path[0]!=2 && path[0]%2==0)
            printf("%d+%d",path[0]/2,path[0]/2);
        else printf("%d",path[0]);
        for(int i=1;i<d;i++)
        {
            if(path[i]!=2 && (path[i]%2==0))
                printf("+%d+%d",path[i]/2,path[i]/2);
            else printf("+%d",path[i]);
        }
        puts("");
        return 1;
    }
    for(;i<p;i++)
    {
        if(pr[i]>n)continue;
        for(int j=2-(pr[i]==2);j>0;j--)
        {
            path[d++]=pr[i]*j;
            if(go(n-j*pr[i],k-j,i+1))
                return 1;
            d--;
        }
    }
    return 0;
}
main()
{
    int i,j,k,n,C=1;
    pr[0]=2;
    for(p=1,i=3;i<300;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*3;j<300;j+=i*2)
            notp[j]=1;
        pr[p++]=i;
    }
    qsort(pr,p,sizeof(pr[0]),prcmp);
    s[0][0]=1;
    for(j=0;j<p;j++)
        for(i=14;i>0;i--)
            for(k=1000;k>=pr[j];k--)
                if(s[i-1][k-pr[j]])
                    s[i][k]=1;
    for(j=0;j<p;j++)
        for(i=14;i>0;i--)
            for(k=1000;k>=pr[j];k--)
                if(s[i-1][k-pr[j]])
                    s[i][k]=1;
    while(scanf("%d %d",&n,&k) && n+k)
    {
        d=0,printf("CASE %d:\n",C++);
        if(!go(n,k,0))
            puts("No Solution.");
    }
}
