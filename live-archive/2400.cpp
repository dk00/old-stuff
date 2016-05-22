#include<set>
#include<cstdio>
main()
{
    int i,j;
    std::set<int> h;
    for(i=0;i*i*i<=151200;i++)
        for(j=0;i*i*i+j*(j+1)*(j+2)/6<=151200;j++)
            h.insert(-i*i*i-j*(j+1)*(j+2)/6);
    while(scanf("%d",&i)==1 && i)
        printf("%d\n",-*h.lower_bound(-i));
}
