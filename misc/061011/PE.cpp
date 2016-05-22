#include<cmath>
#include<cstdio>    //Head and Triling
int pow(int n,int k)
{
    if(!k)return 1;
    if(k%2)
        return((n*pow(n,k-1))%1000);
    int tmp=pow(n,k/2);
    return(tmp*tmp)%1000;
}
main()
{
    int n,i,k,T;
    double fi,fj;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&k);
        fi=log(n)*k+1e-7;
        fj=log(10);
        i=(int)floor(fi/fj);
        if(i>10)
            fi-=fj*(i-3);
        while(fi>=fj*3)fi-=fj;
        printf("%03d...%03d\n",(int)floor(exp(fi)),pow(n%1000,k));
    }
}
