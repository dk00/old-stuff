struct frac
{
    long long a,b;
    void operator=(int s){a=s,b=1;}
    void operator+=(frac s)
    {
        if(b<s.b)
            a*=s.b/b,b*=s.b/b;
        if(s.b<b)
            s.a*=b/s.b,s.b*=b/s.b;
        a+=s.a;
    }
    frac operator*(frac s){return (frac){a*s.a,b*s.b};}
    long long operator*(long long s){return s*a/b;}
};
struct poly
{
    int d;
    frac s[100];
    void init(int n)
    {
        d=n,s[0]=(frac){1,1};
        for(int i=1;i<n;i++)
            s[i]=(frac){1,s[i-1].b*i};
    }
    frac& operator[](int n){return s[n];};
    poly& operator*=(poly& a)
    {
        int i,j;
        poly tmp;
        tmp=*this;
        for(i=0;i<d+a.d-1;i++)
            s[i]=0;
        for(i=0;i<d;i++)
            for(j=0;j<a.d;j++)
                s[i+j]+=a.s[j]*tmp.s[i];
        d+=a.d-1;
        return *this;
    }
};
