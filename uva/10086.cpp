#include<cstdio>
const int inf=20000000;
int s[301],p0[31][301],s1[21],s2[21];
main()
{
    int i,j,k,l,n,m,*p;
    while(scanf("%d %d",&n,&m) && m+n)
    {
        for(i=1;i<=n;i++)s[i]=inf;
        scanf("%d",&m);
        for(l=0;l<m;l++)
        {
            p=p0[l];
            scanf("%d",&j);
            for(k=1;k<=j;k++)
                scanf("%d",s1+k);
            for(k=1;k<=j;k++)
                scanf("%d",s2+k);
            s1[0]=s2[0]=0;
            for(k=0;k<=j;k++)
                s1[k]+=s2[j-k];
            for(i=n;i>=0;i--)
            {
                if(s[i]<inf)s[i]+=s1[0];
                for(k=1;k<=j && i-k>=0;k++)
                    if(s[i-k]+s1[k]<s[i])
                        p[i]=k,
                        s[i]=s[i-k]+s1[k];
            }
        }
        printf("%d\n",s[n]);
        for(i=0,j=m;m--;i++)
        {
            s[i]=p0[m][n];
            n-=p0[m][n];
        }
        while(j--)
            printf("%d%c",s[j],j?' ':'\n');
    }
}
