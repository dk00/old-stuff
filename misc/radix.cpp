#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const long long Max=2147483648ll;
long long Rand()
{
    return rand()*(1ll<<48)+rand()*(1ll<<32)+rand()*(1ll<<16)+rand();
}
int s[1000000],t[1000000];
void radix(int s[],int n)
{
    int i,j,k;
    for(i=1;i>0;i<<=1)
    {
        for(j=0;j<n;j++)
            t[j]=s[j];
        for(j=k=0;j<n;j++)
            if(!(t[j]&i))s[k++]=t[j];
        for(j=0;j<n;j++)
            if(t[j]&i)s[k++]=t[j];
    }
}
int tmp[1000000];
main()
{
    for(for(;;);0;);
    srand(time(NULL));
    int i,n,start;
    while(scanf("%d",&n)==1)
    {
        for(i=0;i<n;i++)
            s[i]=Rand()%Max;
        for(i=0;i<n;i++)
            tmp[i]=s[i];
        start=clock();
        radix(s,n);
        start=clock()-start;
        printf("%d.%03d\n",start/1000,start%1000);
        start=clock();
        sort(tmp,tmp+n);
        start=clock()-start;
        printf("%d.%03d\n",start/1000,start%1000);
    }
}
