#include<stdio.h>
main()
{
    while(1)
    {
        scanf("%d %d",&n,&m);
        scanf("%d %d %d",&x,&y,&r);
        if(n==0 && m==0)
            break;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
                c[i][j]=0;
            for(j=0;j<=r;j++)
                to[j][i]=-1;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            c[i-1][j-1]=k;
        }
        to[1][x]=0;
        for(l=1;l<=r;l++)    //run ?? here
        {
            
        }
    }
}