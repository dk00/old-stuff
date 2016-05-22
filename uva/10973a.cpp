#include<cstdio>
bool mark[3000];
short num[3000],ne[3000][3000];
main()
{
    int i,j,k,n,m,t,r,sum,*tmp;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            num[i]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            i--,j--;
            if(i<j)
                ne[i][num[i]++]=j;
            else
                ne[j][num[j]++]=i;
        }
        for(i=sum=0;i<n;i++)
        {
            for(j=0;j<num[i];j++)
                mark[ne[i][j]]=true;
            for(j=0;j<num[i];j++)
            {
                r=ne[i][j];
                for(k=0;k<num[r];k++)
                    if(mark[ne[r][k]])
                        sum++;
            }
            for(j=0;j<num[i];j++)
                mark[ne[i][j]]=false;
        }
        printf("%d\n",sum);
    }
}
