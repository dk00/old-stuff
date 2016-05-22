#include<cstdio>
main()
{
    int n,a,b[2],*min=b,*max=b+1;
    while(scanf("%d",&n) && n){
        *min=-2147483647;
        *max=2147483647;
        while(n--){
            scanf("%d",&a);
            (*max)<?=a;
            *(max--)=2*a-*max;
            *(min++)=2*a-*min;
        }
        printf("%d\n",(*max-*min+1)>?0);
    }
}

