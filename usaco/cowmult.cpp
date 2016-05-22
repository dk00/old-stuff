/*
PROB:cowmult
LANG:C++
*/
#include<cstdio>

main()
{
    freopen("cowmult.in","r",stdin);
    freopen("cowmult.out","w",stdout);
    char a[99],b[99];
    int i,j,sum;
    scanf("%s %s",a,b);
    for(i=sum=0;a[i];i++)
        for(j=0;b[j];j++)
            sum+=(a[i]-'0')*(b[j]-'0');
    printf("%d\n",sum);
}
