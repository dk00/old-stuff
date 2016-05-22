#include<cstdio>
#define lld "I64d" //change this into "lld" if using Linux.
const int Size=100;
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
    long long s[Size];
    bigint(const char a[]){
        int i;
        for(i=0;a[i];i++);
        for(n=0;(i-=9)>=0;n++)
            sscanf(a+i,"%9"lld,s+n);
        sprintf(__tmp,"%%%d"lld,9+i);
        if(i<0)sscanf(a,__tmp,s+n++);
        s[n]=0;
    }
    bigint(const long long &a){s[1]=a/D,s[0]=a%D,s[2]=0,n=1+!!s[1];}
    bigint(const int &a){*this=0ll+a;}
    bigint(){*this=0;}
    const char *tostr()const{
        int i,j;
        char *t=__tmp;
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
    bigint& operator*=(const bigint &t)
    {
        bigint tmp=*this;
        const long long *a=tmp.s,*b=t.s;
        if(b==s)b=a;
        n+=t.n;
        for(int i=0;i<=n;i++)s[i]=0;
        for(int i=0;i<tmp.n;i++)
            for(int j=0;j<t.n;j++)
            {
                s[i+j]+=a[i]*b[j];
                s[i+j+1]+=s[i+j]/D,s[i+j]%=D;
            }
        while(n>1 && !s[n-1])n--;
        return *this;
    }
/*  inline void operator+=(const int &x)
    {
        s[0]+=x;
        fix();
    }
    inline void operator*=(const int &x)
    {
        for(int i=0;i<n;i++)
            s[i]*=x;
        fix();
    }*/
};
main()
{
    int n;
    char t1[1000],t2[1000];
    bigint a;
    a=0;
    while(scanf("%s %s",t1,t2)==2)
    {
        a=t1;
        puts((a*=t2).tostr());
    }
}
