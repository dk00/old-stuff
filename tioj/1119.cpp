#include<cstdio>
main()
{
    int i,n,t;
    while(scanf("%d",&n)==1)
    {
        for(t=0;n--;)
        {
            scanf("%d",&i);
            t=t*2+i;
        }
        if(t && i>1)
            t=(t-1)*2+1;
        printf("%d\n",t);
    }
}
