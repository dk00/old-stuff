#include<stdio.h>
inline int abs(int n)
{
    if(n<0)
        return -n;
    return n;
}
inline int min(int a,int b)
{
    if(a<b)
        return a;
    return b;
}
main()
{
    int i,n,l1,r1,l2,r2,lc1,lc2,rc1,rc2;
    while(1)
    {
        scanf("%d",&n);
        if(n==0)
            break;
        scanf("%d %d",&l1,&r1);
        lc1=r1+r1-l1-1;
        rc1=r1-1;
        for(i=1;i<n;i++)
        {
            scanf("%d %d",&l2,&r2);
            lc2=min(lc1+abs(r2-l1),rc1+abs(r2-r1));
            rc2=min(lc1+abs(l2-l1),rc1+abs(l2-r1));
            lc1=lc2+r2-l2+1;
            rc1=rc2+r2-l2+1;
            l1=l2,r1=r2;
            //printf("%d %d\n",lc1,rc1);
        }
        printf("%d\n",min(lc1+abs(n-l1),rc1+abs(n-r1)));
    }
}
