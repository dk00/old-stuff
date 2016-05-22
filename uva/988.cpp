#include<cstdio>
int s[1000000];
main()
{
    int i,j,k,n,sum,C=1;
    s[0]=1;
    while(scanf("%d",&n)==1)
    {
        for(i=1;i<n;i++)s[i]=0;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&k);
            if(!k)sum+=s[i];
            while(k--)
            {
                scanf("%d",&j);
                s[j]+=s[i];
            }
        }
        if(C)C=0;
        else puts("");
        printf("%d\n",sum);
    }
}
