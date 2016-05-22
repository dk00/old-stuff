#include<cstdio>
char notp[1001];
int p[300];
main()
{
    int i,j,k,n,m;
    p[0]=1,p[1]=2;
    n=2;
    for(i=3;i<1010;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<1000;j+=i*2)notp[j]=1;
        p[n++]=i;
    }
    while(scanf("%d %d",&m,&k)==2)
    {
        printf("%d %d:",m,k);
        for(i=0;p[i]<=m;i++);
        m=i;
        if(m%2)
            for(i=(m/2-k+1)>?0;i<m && i<m/2+k;i++)
                printf(" %d",p[i]);
        else
            for(i=(m/2-k)>?0;i<m && i<m/2+k;i++)
                printf(" %d",p[i]);
        puts("\n");
    }
}
