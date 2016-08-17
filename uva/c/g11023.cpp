#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int num[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
main()
{
    srand(time(NULL));
    int i,j,n,s[100];
    long long max,f[21];
    for(i=f[0]=1;i<21;i++)
        f[i]=f[i-1]*i;
    printf("derive (");
    n=20;
    max=f[n];
    for(i=0;i<n;i++)
        s[i]=1+rand()%20;
    sort(s,s+n);
    printf("%d",s[0]);
    for(i=1,j=1;i<n;i++)
    {
        printf(",%d",s[i]);
        if(s[i]!=s[i-1])max/=f[j],j=1;
        else j++;
    }
    max/=f[j];
    printf(") %d %I64d\nend",n-2,1ll*rand()%1000);
}
