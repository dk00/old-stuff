#include<cstdio>
main()
{
    freopen("cutein.txt","r",stdin);
    freopen("cuteout.txt","w",stdout);
    int i,j,n;
    j=0,scanf("%d",&n);
    while(n--)
    {
        scanf("%d",&i);
        if(i)j=0;
        else j++;
    }
    printf("%d\n",j);
}
