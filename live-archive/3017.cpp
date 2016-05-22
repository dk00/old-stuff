#include<cstdio>
#include<cstdlib>
int Rand()
{
    return (rand()*(1<<16))^(rand()*(1<<8))^rand();
}
int pow(long long n,int k,int m)
{
    if(k==0)return 1;
    if(k%2==1)
        return n*pow(n,k-1,m)%m;
    n=pow(n,k/2,m);
    return n*n%m;
}
bool witness(int a,int n)
{
    int x,y,u,t;
    for(u=n-1,t=0;u%2==0;u/=2,t++);
    x=pow(a,u,n);
    while(t--)
    {
        y=x;
        x=pow(x,2,n);
        if(x==1 && y!=1 && y!=n-1)
            return 1;
    }
    return x!=1;
}
bool mr(int n,int s=25)
{
    /*int a=min(n-1,(long long)floor(2*log(n)*log(n)));
    while(a>=2)
        if(witness(a--,n))
            return 0;*/
    if(n-1>=2 && witness(2,n))return 0;
    if(n-1>=3 && witness(3,n))return 0;
    if(n-1>=7 && witness(7,n))return 0;
    if(n-1>=61 && witness(61,n))return 0;
    if(n-1>=24251 && witness(24251,n))return 0;
    return 1;
}
template<class x> x swap(x &a,x &b){x tmp=a;a=b;b=tmp;}
char go(int x)
{
    int i,j,k,n;
    char c,tmp[50];
    sprintf(tmp,"%d",x);
    for(n=0;tmp[n];n++);
    for(i=0;i<900;i++)
    {
        for(j=0;j<n;j++)
            swap(tmp[j],tmp[rand()%n]);
        sscanf(tmp,"%d",&j);
        j=abs(x-j)/9;
        if(j>1 && mr(j))return 1;
    }
    return 0;
}
main()
{
    int i,j,k,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&i,&j);
        if(i>j)swap(i,j);
        for(k=0;i<=j;i++)
            if(go(i))k++;
        printf("%d\n",k);
    }
}
