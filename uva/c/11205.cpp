#include<cstdio>
int test(int n)
{
    if(n)return n%2+test(n/2);
    return 0;
}
main()
{
    int i,j,k,n,m,T,min,s[100];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&m,&n);
        min=m;
        for(i=0;i<n;i++)
            for(j=s[i]=0;j<m;j++)
            {
                scanf("%d",&k);
                s[i]=s[i]*2+k;
            }
        for(k=(1<<m)-1;k>=0;k--)
        {
            for(i=0;i<n;i++)
                for(j=0;j<i;j++)
                    if((s[i]&k)==(s[j]&k))
                        goto fail;
            min<?=test(k);
            fail:;
        }
        printf("%d\n",min);
    }
}
