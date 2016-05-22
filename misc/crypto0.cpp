#include<cstdio>
struct Poly
{
    unsigned x;
    Poly(unsigned a):x(a){}
    Poly& operator+=(Poly a){
        x^=a.x;
        return *this;
    }
    Poly operator+(Poly a)const{
        return x^a.x;
    }
    Poly operator*(Poly a)const{
        Poly res(0);
        for(int i=0;i<32;i++)
            if((1u<<i)&a.x)
                res+=x;
        return res;
    }
    Poly operator%=(Poly a){
        unsigned i,j;
        for(i=1;a.x && (a.x<<i>>i)==a.x;i++);
        for(j=31;i--;j--)
            if(x&(1<<j))
                x^=a.x;
    }
    Poly operator%(Poly a)const{
        Poly res=*this;
        return res%=a;
    }
};
main()
{
    int i,n,m;
    while(scanf("%d %d",&n,&m)==2){
        for(i=0;i<1u<<n;i++)
            if((Poly(i)*Poly(i)%Poly(m)).x==1)
                printf("%d\n",i);
    }
}
