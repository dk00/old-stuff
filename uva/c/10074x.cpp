#include<cstdio>
main()
{
    int i,j,k,l,n,m,u,max,s[101],len[101],st[101];
    len[0]=0;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(j=0;j<m;j++)
            s[j]=0;
        for(i=max=0;i<n;i++)
        {
            for(j=0,k=1;j<m;j++)
            {
                scanf("%d",&u);
                if(u)s[j]=0;
                else s[j]++;
                if(s[j]>len[k-1])
                {
                    len[k]=s[j];
                    st[k++]=j;
                    continue;
                }
                while(s[j]<len[k-1])
                    k--,max>?=len[k]*(j-st[k]);
                if(s[j]>len[k-1])
                    len[k++]=s[j];
            }
            while(0<len[k-1])
                k--,max>?=len[k]*(j-st[k]);
        }
        printf("%d\n",max);
    }
}
