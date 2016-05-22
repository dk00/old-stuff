#include<cstdio>
char s[1<<19];
main()
{
    int i,j,k,n,C=1;
    for(i=(1<<19)-1;i>=0;i--)
        s[i]='?';
    while(scanf("%d",&n) && n)
    {
        k=0;
        for(i=0;i<n;i++)
        {
            scanf("%d",&j);
            k|=(1<<(j-2));
        }
        for(i=0;i<19;i++)
            if(!go(move(k,i)))
                break;
        printf("Test Case #%d\n",C++);
        if(i<19)
        {
            printf("The winning moves are:");
            for(;i<19;i++)
                printf(" %d",i+2);
            puts("");
        }
        else puts("There's no winning move");
    }
}
