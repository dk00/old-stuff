#include<cstdio>
#include<cstring>
int u[100000];
main()
{
    int h,i,j,k,l,n,m;
    while(scanf("%d %d",&m,&n) && n+m)
    {
        memset(u,0,sizeof(u));
        u[0]=1;
        for(i=l=0;i<n;i++)
        {
            scanf("%d",&h);
            l=(l+h%m)%m;
            if(u[l])
                j=u[l],k=i+1;
            u[l]=i+2;
        }
        for(;j<k;j++)
            printf("%d ",j);
        printf("%d\n",k);
    }
}
