#include<cstdio>
main()
{
    int i,j,t,C=1,s[101];
    s[0]=0;
    for(i=1;i<=100;i++)
        s[i]=s[i-1]+i*(i%2);
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&i,&j);
        printf("Case %d: %d\n",C++,s[j]-(i?s[i-1]:0));
    }
}
