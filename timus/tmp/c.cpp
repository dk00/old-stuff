#include<cstdio>
int gcd(int a,int b)
{
    while((a%=b)&& a &&(b%=a));
    return a+b;
}
struct frac
{
    int p,q;
    frac(){}
    frac(int a,int b){p=a,q=b;}
    frac(int a){p=a,q=1;}
    void reduce()
    {
        int d=gcd(p,q);
        p/=d,q/=d;
    }
    frac& operator+=(frac a)
    {
        p=p*a.q+a.p*q;
        q*=a.q;
        reduce();
    }
    frac& operator*=(frac a)
    {
        p*=a.p;
        q*=a.q;
        reduce();
    }
    frac operator*(frac a)const
    {
        frac tmp=*this;
        tmp*=a;
        return tmp;
    }
    void print()
    {
        printf("%d/%d\n",p,q);
    }
}_s1[2009],_s2[2009];
main()
{
    int i,j,k,x,n,m;
    frac sum,*s1,*s2;
    while(~scanf("%d %d %d",&n,&m,&x))
    {
        s1=_s1+m+1001;
        s2=_s2+m+1001;
        for(i=m-x;i<=m+x;i++)
            s1[i]=s2[i]=0;
        s2[m]=1;
        for(k=0;k<x;k++)
        {
            for(i=m-k;i<=m+k;i++)
                s1[i]=s2[i],s2[i]=0;
            for(i=m-k;i<=m+k;i++)
            {
                frac t1(i,n),t2(n-i,n);
                s2[i-1]+=s1[i]*t1;
                s2[i+1]+=s1[i]*t2;
            }
        }
        for(i=m-k,sum=0;i<=m+k;i++)
            sum+=s2[i]*i;
        sum.print();
    }
}
