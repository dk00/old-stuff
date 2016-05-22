#include<cstdio>
main()
{
    long long i,j,k,l,n,m,s,C=1;
    while(scanf("%lld %lld",&n,&m) && n+m)
    {
        s=0;
        scanf("%lld %lld %lld %lld",&i,&j,&k,&l);
        if(((i<?j)+(i!=j))*(n*m-m)<((k<?l)+(k!=l))*(n*m-n))
        {
            i+=k,k=i-k,i-=k;
            j+=l,l=j-l,j-=l;
            m+=n,n=m-n,m-=n;
        }
        if(i+j)s+=(2*(i<?j)+(i!=j))*(n*m-m)+m;
        n--;
        if(i>j)i-=j+1,j=0;
        else if(j>i)j-=i+1,i=0;
        else i=j=0;
        if(k+l)s+=(2*(k<?l)+(k!=l))*(n*m-n)+n;
        if(k>l)k-=l+1,l=0;
        else if(l>k)l-=k+1,k=0;
        else k=l=0;
        i+=j,k+=l;
        while(n+m && i+k)
        {
            if(i && n>=m)
                i--,s+=n--*m;
            else
                k--,s+=n*m--;
        }
        printf("Case %lld: %lld\n",C++,s);
    }
}
