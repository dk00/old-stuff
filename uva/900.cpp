#include<cstdio>
main()
{
    int i,s[51];
    s[1]=1,s[2]=2;
    for(i=3;i<=50;i++)
        s[i]=s[i-1]+s[i-2];
    while(scanf("%d",&i) && i)
        printf("%d\n",s[i]);
}
