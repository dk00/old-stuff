#include<cstdio>
int pow(int n,int k)
{
    if(!k)return 1;
    if(k%2)return n*pow(n,k-1);
    n=pow(n,k/2);
    return n*n;
}
main()
{
    int n,k;
    while(scanf("%d %d",&k,&n)>0 && n+k)
        printf("%d\n",(pow(k,n)+(n-1)*k+n*pow(k,(n+1)/2))/n/2);
}
