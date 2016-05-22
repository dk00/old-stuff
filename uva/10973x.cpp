#include<cstdio>
char c[3000][3000];
main()
{
    int i,j,k,n,m,t,r,sum;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<i;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            if(i<j)
                c[i][j]=1;
            else
                c[j][i]=1;
        }
        for(i=sum=0;i<n;i++)
            for(j=i+1;j<n;j++)
            {
                if(!c[i][j])
                    continue;
                for(k=j+1,r=1;k<n;k++)
                    if(c[i][k] && c[j][k])
                    {
                        sum++;
                        if(!r--)
                            break;
                    }
            }
        printf("%d\n",sum);
    }
}
