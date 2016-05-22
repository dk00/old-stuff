#include<cstdio>
int w[1000],l[1000],min[1001];
main()
{
    int i,j,n,max;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
        {
            min[i+1]=500000000;
            scanf("%d %d",&w[i],&l[i]);
        }
        min[0]=0;
        for(i=n,max=0;i--;)
        {
            for(j=max;min[j]>l[i] && j>0;j--);
            if(min[j]+w[i]<min[j+1])
                min[j+1]=min[j]+w[i];
            if(j+1>max)max=j+1;
        }
        printf("%d\n",max);
    }
}
