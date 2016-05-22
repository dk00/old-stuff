#include<cstdio>
const int inf=2147483647;
int s[1001],t[20];
main()
{
    int i,j,k,l,n,sum,C=0;
    while(scanf("%d",&n) && n)
    {
        for(l=1;l<1000;l++)s[l]=-inf;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&j),sum+=j;
            for(k=0;k<j;k++)
            {
                scanf("%d",t+k),t[k]=10-t[k];
                if(k)t[k]+=t[k-1];
            }
            for(l=sum;l>=0;l--)
                for(k=0;l+k+1<=sum && k<j;k++)
                    if(s[l]>-inf && s[l]+t[k]>s[l+k+1])
                        s[l+k+1]=s[l]+t[k];
        }
        for(k=l=0;l<=sum;l++)k>?=s[l];
        if(C++)puts("");
        printf("Workyards %d\n",C);
        printf("Maximum profit is %d.\n",k);
        printf("Number of pruls to buy:");
        for(l=0,j=10;j>0 && l<=sum;l++)
            if(s[l]==k)
                printf(" %d",l),j--;
        puts("");
    }
}
