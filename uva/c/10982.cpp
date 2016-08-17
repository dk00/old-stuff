#include<cstdio>
#include<cstdlib>
struct pt{int x,y;}s[5000];
int u[101];
main()
{
    int i,j,k,n,m,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<m;i++)
            scanf("%d %d",&s[i].x,&s[i].y);
        while(1)
        {
            for(i=1,k=0;i<=n;i++)k+=(u[i]=rand()%2);
            for(i=j=0;i<m;i++)
                if(u[s[i].x]==u[s[i].y])j++;
            if(j<=m/2)break;
        }
        printf("Case #%d: %d\n",C++,k);
        for(i=1;u[i]==0;i++);
        printf("%d",i++);
        for(;i<=n;i++)
            if(u[i])printf(" %d",i);
        puts("");
    }
}
