#include<cstdio>
int u[10000];
main()
{
    int i,j,k,x,n,m;
    while(scanf("%d %d %d",&n,&k,&m)==3)
    {
        for(j=0;j<m+k;j++)u[j]=-1;
        for(i=1,x=n%m;;i++)
        {
            if(u[x]>=0)break;
            u[x]=i,x*=n;
            if(x>k)x=k+(x-k)%m;
        }
        printf("%d %d\n",u[x],i-u[x]);
    }
}
