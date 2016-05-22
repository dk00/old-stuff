#include<ctime>
#include<cstdio>
#include<cstdlib>
const int n=500;
int s[505];
main()
{
    int i,m;
    freopen("ppairing.in","w",stdout);
    for(i=m=0;i<n;i++)
    {
        s[i]=rand()%150*2;
        m+=s[i];
    }
    printf("%d %d\n",m,n);
    for(i=0;i<n;i++)
        printf("%d\n",s[i]);
}
