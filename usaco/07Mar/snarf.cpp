/*
PROG: snarf
LANG: C++
ID: s0000151
*/
#include<cstdio>
main()
{
    freopen("snarf.in","r",stdin);
    freopen("snarf.out","w",stdout);
    int i,j,n;
    long long s1,s2;
    scanf("%d",&n);
    for(i=j=1,s1=s2=0;;s2+=++i)
    {
        while(s2>s1)
        {
            s1+=j++;
            s2-=j;
        }
        if(s1==s2 && j>n)break;
    }
    printf("%d %d\n",j,i);
    scanf(" ");
}
