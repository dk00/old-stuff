#include<cmath>
#include<cstdio>
int pow(int n,int k)
{
    if(k==0)
        return 1;
    if(k%2)
        return(pow(n,k-1)*(n%1000))%1000;
    int tmp=pow(n,k/2);
    return(tmp*tmp)%1000;
}
main()
{
    int n,k,t,n1,n2;
    double p;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&k);
        n2=pow(n,k);
        p=log10((double)n)*k;
        p=p-floor(p)+2;
        n1=(int)pow(10.0,p);
        printf("%.0lf...%03d\n",pow(10.0,p),n2);
    }
}
