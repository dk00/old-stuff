/*
PROB: ride
LANG: C++
*/
#include<cstdio>
main()
{
    int i,j,k;
    char a[99],b[99];
    freopen("ride.in","r",stdin);
    freopen("ride.out","w",stdout);
    scanf("%s %s",a,b);
    for(i=0,j=1;a[i];i++)
        j=j*(a[i]-'A'+1)%47;
    for(i=0,k=1;b[i];i++)
        k=k*(b[i]-'A'+1)%47;
    if(j==k)puts("GO");
    else puts("STAY");
    scanf(" ");
}
