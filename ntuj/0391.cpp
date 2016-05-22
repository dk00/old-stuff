#include<cstdio>
const int M=32771;
int pow(int n,int k)
{
    if(!k)return 1;
    if(k%2)return n*pow(n,k-1)%M;
    n=pow(n,k/2);
    return n*n%M;
}
int s[M];
void go(int x,int r=1)
{
    int i;
    while(x)
    {
        for(i=0;i<M;i++)
            s[i]+=x/M*r;
        for(i=x%M;i>0;i--)
            s[i]+=r;
        x/=M;
    }
}
main()
{
    int i,n,k,T;
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<M;i++)
            s[i]=0;
        scanf("%d %d",&n,&k);
        go(n);
        go(n-1);
        go(k,-1);
        go(k-1,-1);
        go(n-k,-1);
        go(n-k+1,-1);
        for(i=0;i<M;i++)
            if(s[i]<0)
                s[pow(i,M-2)]-=s[i],s[i]=0;
        for(i=0,k=1;i<M;i++)
            k=k*pow(i,s[i])%M;
        printf("%d\n",k);
    }
}
