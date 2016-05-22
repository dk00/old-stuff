#include<cstdio>
#define lld "I64d" //change this into "lld" if using Linux.
const int Size=350;
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
    bigint(const int &a){s[0]=a,n=1;}
    bigint(){*this=0;}
    const char *tostr(char *t=__tmp)const
    {
        int i,j;
        sprintf(t,"%lld",s[n-1]);
        for(i=0;t[i];i++);
        for(j=n-2;j>=0;j--,i+=9)
            sprintf(t+i,"%09lld",s[j]);
        return t;
    }
    bigint& operator*=(const bigint &t)
    {
        bigint tmp=*this;
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
};
bigint c[200];
main()
{
    c[0]=1;
    c[1]=1;
    int i,n;
    for(i=2;i<200;i++)
    {
        c[i]=c[i-1];
        c[i]*=(4*i-2);
        c[i]/=(i+1);
    }
    scanf("%d",&n);
    for(i=0;i<2*n-1;i++)
        puts(c[i].tostr());
}
