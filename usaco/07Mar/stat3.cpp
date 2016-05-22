/*
PROG: stat3
LANG: C++
ID: s0000151
*/
#include<cstdio>
main()
{
    freopen("stat3.in","r",stdin);
    freopen("stat3.out","w",stdout);
    int i,j,k,n,sum;
    scanf("%d",&n);
    sum=0;
    for(i=j=0;i<n;i++)
    {
        scanf("%d",&k);
        if(k>0)sum+=k*100,j++;
    }
    printf("%d\n",(sum/j+5)/10);
    scanf(" ");
}
