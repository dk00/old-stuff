#include<cstdio>
#include<cstdlib>
int p[5010],m[5010],dg[5010],c[10010],q[5010],l[5010];
main()
{
    int i,j,k,n;
    while(scanf("%d",&n)==1)
    {
        for(i=1;i<=n;i++)
        {
            scanf("%d",&m[i]);
            p[i]=-1,dg[i]=m[i];
            if(i)
                m[i]+=m[i-1];
            for(j=m[i-1];j<m[i];j++)
                scanf("%d",&c[j]);
        }
        for(i=1,j=0;i<=n;i++)
            if(dg[i]==1)
                l[i]=0,q[j++]=i;
            else
                l[i]=-1;
        for(i=0;i<j;i++)
        {
            if(i==j-2 && j==n && l[q[j-1]]==l[q[j-2]])
                break;
            for(k=m[q[i]-1];k<m[q[i]];k++)
            {
                dg[c[k]]--;
                if(l[c[k]]==-1 || (j==n && c[k]==q[j-1]))
                    p[q[i]]=c[k];
                if(dg[c[k]]==1)
                {
                    l[c[k]]=l[q[i]]+1;
                    q[j++]=c[k];
                }
            }
        }
        printf("Best Roots :");
        if(j>1 && l[q[j-2]]==l[q[j-1]])
        {
            if(q[j-1]<q[j-2])
                printf(" %d %d\n",q[j-1],q[j-2]);
            else
                printf(" %d %d\n",q[j-2],q[j-1]);
        }
        else printf(" %d\n",q[j-1]);
        k=0;
        while(j--)
        {
            if(p[q[j]]>=0)
            {
                l[q[j]]=l[p[q[j]]]+1;
                k>?=l[q[j]];
            }
            else l[q[j]]=0;
        }
        printf("Worst Roots :");
        for(i=1;i<=n;i++)
            if(l[i]==k)
                printf(" %d",i);
        puts("");
    }
}
