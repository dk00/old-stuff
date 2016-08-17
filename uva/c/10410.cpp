#include<cstdio>
int s1[1000],s2[1000],d[1001],p[1001];
main()
{
    int i,j,n,nd;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            scanf("%d",&s1[i]);
        for(i=0;i<n;i++)
            scanf("%d",&s2[i]);
        d[s1[0]]=0;
        for(i=nd=1,j=0;i<n;i++)
        {
            for(;j<n && s1[i]!=s2[j];j++);
            if(j>=n)
                j=0,nd++,i--;
            else
                d[s2[j]]=nd;
        }
        for(i=0;i<n;i++)
            for(j=i+1;d[s2[i]]<d[s2[j]] && j<n;j++)
                if(d[s2[i]]+1==d[s2[j]])
                    p[s2[j]]=s2[i];
        for(i=1;i<=n;i++)
        {
            printf("%d:",i);
            for(j=1;j<=n;j++)
                if(p[j]==i)
                    printf(" %d",j);
            puts("");
        }
    }
}
