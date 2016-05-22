#include<cstdio>
#include<algorithm>
int go(int st,int ed)
{

}
main()
{
    while(scanf("%d %d",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=inf;
        for(i=0;i<n;i++)
            scanf("%d",p+i);
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i][j]=c[j][i]=k;
        }
        scanf("%d",&q);
        while(q--)
        {
            scanf("%d %d %d",max,&i,&j);
            k=go(i,j);
            if(k<inf)
                printf("%d\n",k);
            else
                puts("impossible");
        }
    }
}
