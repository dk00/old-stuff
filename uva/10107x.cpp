#include<cstdio>
#include"bst.h"
main()
{
    int i,n=0;
    bst<int> s;
    while(scanf("%d",&i)==1)
    {
        n++;
        s.ins(i);
        if(n%2)
            printf("%d\n",s.nth(n/2+1));
        else
            printf("%d\n",(s.nth(n/2+1)+s.nth(n/2))/2);
    }
}
