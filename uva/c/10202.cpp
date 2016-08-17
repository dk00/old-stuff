#include<cstdio>
#include<cstdlib>
int a[11],s[99],use[99];
int numcmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}
main()
{
    int i,j,k,l,n,m,go,sum;
    while(scanf("%d",&n)==1)
    {
        m=n*(n-1)/2;
        for(i=0;i<m;i++)
            scanf("%d",&s[i]);
        qsort(s,m,sizeof(s[0]),numcmp);
        for(l=2,go=0;go==0 && l<n;l++)
        {
            if((s[0]+s[1]+s[l])%2)
                continue;
            sum=(s[0]+s[1]+s[l])/2;
            for(i=0;i<m;i++)
                use[i]=1;
            a[0]=sum-s[l],a[1]=sum-s[1],a[2]=sum-s[0];
            use[0]=use[1]=use[l]=0;
            for(go=1,i=3;go && i<n;i++)
            {
                for(j=0;use[j]==0;j++);
                a[i]=s[j]-a[0];
                for(j=0;go && j<i;j++)
                    for(k=go=0;go==0 && k<m;k++)
                        if(use[k] && s[k]==a[i]+a[j])
                            go=1,use[k]=0;
            }
        }
        if(go==0)
        {
            puts("Impossible");
            continue;
        }
        printf("%d",a[0]);
        for(i=1;i<n;i++)
            printf(" %d",a[i]);
        puts("");
    }
}
