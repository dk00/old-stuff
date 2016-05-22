#include<cstdio>
main()
{
    int i,j,k;
    for(i=0;i<19683;i++)
    {
        for(j=0,k=i;j<9;j++,k/=3)
            printf("%d ",k%3);
        puts("");
    }
}
