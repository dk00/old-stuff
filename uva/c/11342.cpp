#include<cstdio>
bool sq[50001];
int a[50000],b[50001];
main()
{
    int i,j,k,n,T;
    for(i=0;i*i<=50000;i++)
        for(j=0;i*i+j*j<=50000;j++)
            if(!sq[k=i*i+j*j])
                sq[k]=1,a[k]=i,b[k]=j;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(i=0;i*i<=n;i++)
            if(sq[k=n-i*i])
            {
                printf("%d %d %d\n",i,a[k],b[k]);
                break;
            }
        if(i*i>n)puts("-1");
    }
}
