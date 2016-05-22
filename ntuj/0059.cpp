#include<cstdio>
char s[1201][1201];
int x[50];
main()
{
    int i,j,k,n,sum,min;
    while(scanf("%d",&n) && n)
    {
        min=2147483647;
        for(i=sum=0;i<n;i++)
            scanf("%d",x+i),sum+=x[i];
        for(i=0;i<=sum;i++)
            for(j=0;j<=sum;j++)
                s[i][j]=0;
        s[0][0]=1;
        for(i=0;i<n;i++)
            for(j=sum;j>=0;j--)
                for(k=sum;k>=0;k--)
                    if((j>=x[i] && s[j-x[i]][k]) || (k>=x[i] && s[j][k-x[i]]))
                        s[j][k]=1;
        for(j=0;j<=sum;j++)
            for(k=0;k<=sum;k++)
                if(s[j][k])
                    min<?=(j>?k>?(sum-j-k));
        printf("%d\n",min);
    }
}
