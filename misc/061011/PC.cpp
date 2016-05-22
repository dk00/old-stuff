#include<cstdio>
int r[][3]={{1,1,1},{1,1,-1},{1,-1,1},{1,-1,-1}};   //Space
int abs(int a)
{
    if(a<0) return -a;
    return a;
}
main()
{
    int i,j,k,l,n,T,C=1,min[4],max[4];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        scanf("%d %d %d",&i,&j,&k);
        for(l=0;l<4;l++)
            max[l]=min[l]=i*r[l][0]+j*r[l][1]+k*r[l][2];
        n--;
        while(n--)
        {
            scanf("%d %d %d",&i,&j,&k);
            for(l=0;l<4;l++)
            {
                min[l]<?=(i*r[l][0]+j*r[l][1]+k*r[l][2]);
                max[l]>?=(i*r[l][0]+j*r[l][1]+k*r[l][2]);
            }
        }
        for(l=k=0;l<4;l++)
            k>?=abs(min[l]-max[l]);
        printf("Case #%d: %d\n",C++,k);
    }
}
