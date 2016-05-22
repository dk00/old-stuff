#include<cstdio>
main()
{
    int i,n,t;
    for(n=0;n<5;n++)
    {
        scanf("%d %d",&i,&t);
        if(i%2 || t%2 || (i==0 && t==0))
            puts("1");
        else puts("0");
    }
}
