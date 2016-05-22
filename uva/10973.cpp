#include<stdio.h>
short int v[3000],s[3000][3000];
main()
{
    int i,j,t,n,m,a,b,u=0,sum;
    scanf("%d",&t);
    while(u+=3,t--)
    {
        sum=0;
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            v[i]=0;
        while(m--)
        {
            scanf("%d %d",&a,&b);
            a--,b--;
            if(v[a]<1 || v[b]<1)
            {
                s[a][b]=u+1,s[b][a]=u+1;
                continue;
            }
            for(i=0,j=1;i<n;i++)
                if(s[a][i]>=u && s[b][i]>=u)
                {
                    s[a][i]--,s[i][a]--;
                    s[b][i]--,s[i][b]--;
                    sum++;
                    if(--j<0)
                        break;
                }
            if(j>=0)
                s[a][b]=u+j,s[b][a]=u+j;
        }
        printf("%d\n",sum);
    }
}
