#include<cstdio>
int s[99],u[10001];
main()
{
    int i,j,n,m,sum,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<10000;i++)u[i]=-1;
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            s[i]=0;
            scanf("%d",&m);
            while(m--)
            {
                scanf("%d",&j);
                if(u[j]<0)u[j]=i,s[i]++;
                else if(u[j]!=i)s[u[j]]--,u[j]=n;
            }
        }
        for(i=sum=0;i<n;i++)
            sum+=s[i];
        printf("Case %d:",C++);
        for(i=0;i<n;i++)
            printf(" %lf%%",100.0*s[i]/sum);
        puts("");
    }
}
