#include<cstdio>
#include<cstring>
int f(int n,int k)
{
    if(n<=k)return n;
    return n*f(n-k,k);
}
main()
{
    int n,k;
    char tmp[100];
    while(scanf("%d %s",&n,tmp)==2)
    {
        k=strlen(tmp);
        printf("%d\n",f(n,k));
    }
}
