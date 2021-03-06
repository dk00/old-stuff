#include<cstdio>
#define lld "I64d" //change this into "lld" if using Linux.
const int Size=5000;
const long long D=1000000000ll;
char __tmp[(Size+5)*9];
class bigint
{
    void fix(){
        s[n]=0;
        for(int i=0;i<n;i++)
            s[i+1]+=s[i]/D,s[i]%=D;
        if(s[n])n++;
        s[n]=0;
    }
public:
    int n;
    long long *s;
    bigint(const char a[])
    {
        s=new long long[Size];
        int i;
        for(i=0;a[i];i++);
        for(n=0;(i-=9)>=0;n++)
            sscanf(a+i,"%9"lld,s+n);
        sprintf(__tmp,"%%%d"lld,9+i);
        if(i+9>0)sscanf(a,__tmp,s+n++);
        s[n]=0;
    }
    bigint(const long long &a)
    {s=new long long[Size];s[1]=a/D,s[0]=a%D,s[2]=0,n=1+!!s[1];}
    bigint(const int &a){s=new long long[Size];*this=0ll+a;}
    bigint()
    {
        s=new long long[Size];
        *this=0;
    }
    ~bigint(){delete[] s;}
    bigint &operator=(bigint x)
    {
        for(n=0;n<x.n;n++)
            s[n]=x.s[n];
    }
    const char *tostr(char *t=__tmp)const
    {
        int i,j;
        sprintf(t,"%lld",s[n-1]);
        for(i=0;t[i];i++);
        for(j=n-2;j>=0;j--,i+=9)
            sprintf(t+i,"%09lld",s[j]);
        return t;
    }
    bigint& operator+=(const bigint &t)
    {
        for(int i=n;i<=t.n;i++)s[i]=0;
        if(n<t.n)n=t.n;
        for(int i=0;i<t.n;i++)
            s[i]+=t.s[i];
        fix();
        return *this;
    }
    bool operator<(bigint t)const
    {
        if(n!=t.n)return n<t.n;
        for(int i=n-1;i>=0;i--)
            if(s[i]!=t.s[i])return s[i]<t.s[i];
        return 0;
    }
    bigint& operator-=(const bigint &t)
    {
        if(*this<t)return *this;
        for(int i=0;i<t.n;i++)
        {
            s[i]-=t.s[i];
            if(s[i]<0)s[i]+=D,s[i+1]--;
        }
        while(n && !s[n-1])n--;
    }
    bigint& operator*=(const bigint &t)
    {
        bigint tmp;
        tmp=*this;
        const long long *a=tmp.s,*b=t.s;
        if(b==s)b=a;
        n+=t.n;
        for(int i=0;i<=n;i++)s[i]=0;
        for(int i=0;i<tmp.n;i++)
        {
            for(int j=0;j<t.n;j++)
                s[i+j]+=a[i]*b[j];
            for(int j=0;j<n;j++)
                s[j+1]+=s[j]/D,s[j]%=D;
        }
        while(n>1 && !s[n-1])n--;
        return *this;
    }
    bigint& operator/=(const int &t)
    {
        int i;
        for(i=n-1;i>0;i--)
            s[i-1]+=(s[i]%t)*D,s[i]/=t;
        s[0]/=t;
        while(n>1 && !s[n-1])n--;
        return *this;
    }

    bigint& operator<<=(int x)
    {
        for(int i=n-1;i>=0;i--)
            s[i+x]=s[i],s[i]=0;
        s[n+=x]=0;
    }
    bigint& mul(bigint x)
    {
        if(n<4 && x.n<4)
            return *this*=x;
        int i,j;
        while(n<x.n)s[n++]=0;
        while(x.n<n)x.s[x.n++]=0;
        bigint a,b,c;
        for(i=n/2,a.n=b.n=c.n=0;i<n;i++,a.n++,b.n++,c.n++)
        {
            a.s[a.n]=s[i];
            c.s[c.n]=b.s[b.n]=x.s[i];
        }
        j=n,n/=2,x.n/=2;
        a+=*this;
        b+=x;
        a.mul(b);
        n=j;
        for(i=n/2,b.n=0;i<n;i++,b.n++)
            b.s[b.n]=s[i];
        b.mul(c);
        n=x.n;
        mul(x);
        a-=b;
        a-=*this;
        a<<=j/2;
        b<<=j&~1;
        *this+=a;
        *this+=b;
        fix();
        return *this;
    }
};
char s1[100000],s2[100000];
main()
{
    while(scanf("%s %s",s1,s2)==2)
        puts((bigint(s1).mul(s2)).tostr());
}
