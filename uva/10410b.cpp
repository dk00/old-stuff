#include<cstdio>
int s[1001],s1[1001],s2[1001],v[1001],p[1001],u[1001],x[1001];
main()
{
    int i,j,k,n;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
        {
            scanf("%d",&s1[i]);
            v[s1[i]]=i,u[i+1]=x[i+1]=0;
        }
        for(i=0;i<n;i++)
            scanf("%d",&s2[i]);
        s[0]=s2[0];
        for(i=j=1;i<n;i++)
        {
            while(j>0 &&(v[s[j-1]]>v[s2[i]] || s2[i]<u[j] || v[s2[i]]<x[j]))
                x[j]=u[j--]=0;
            p[s2[i]]=s[j-1];
            x[j]=v[s2[i]],u[j]=s[j++]=s2[i];
        }
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
