#include<cstdio>
int s[10001];
short u[2000001];
main()
{
    int i,j,k,n,min;
    short t;
    for(t=1;scanf("%d",&n)==1;t++)
    {
        for(i=0,min=2000000000;i<n;i++)
            scanf("%d",&s[i]);
        scanf("%d",&j);
        for(i=0;i<n;i++)
            u[s[i]]=t;
        for(i=0;i<n;i++)
            if(j-s[i]>=0 && u[j-s[i]]==t)
                if(j-2*s[i]>=0 && j-2*s[i]<min)
                    min=j-2*s[i],k=s[i];
        printf("Peter should buy books whose prices are %d and %d.\n\n",
        k,j-k);
    }
}
