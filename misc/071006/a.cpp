#include<cstdio>
int s[100001];
main()
{
    int i,j,k;
    for(i=j=1;i<=10000;i+=j++)
        for(k=0;k<j;k++)
            s[i+k]=s[i+k-1]+j;
    while(scanf("%d",&i) && i)
        printf("%d %d\n",i,s[i]);
}
