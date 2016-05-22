#include<cstdio>
#define lld "lld"
const int Size=120000;
const long long D=1000000000ll;
char __tmp[(Size+5)*9];
class bigint
{
    void fix()
    {
        s[n]=0;
        for(int i=0;i<n;i++)
            s[i+1]+=s[i]/D,s[i]%=D;
        if(s[n])n++;
        s[n]=0;
    }
public:
    int n;
    long long s[Size];
    bigint(const int &a){s[0]=a%D,n=((s[1]=a/D)?2:1);}
    bigint(){*this=0;}
    const char *tostr()const
    {
        int i,j;
        char *t=__tmp;
        sprintf(t,"%lld",s[n-1]);
        for(i=0;t[i];i++);
        for(j=n-2;j>=0;j--,i+=9)
            sprintf(t+i,"%09lld",s[j]);
        return t;
    }
    bigint& operator+=(const bigint& t)
    {
        for(int i=n;i<=t.n;i++)s[i]=0;
        if(n<t.n)n=t.n;
        for(int i=0;i<t.n;i++)
            s[i]+=t.s[i];
        fix();
        return *this;
    }
    bigint& operator*=(const int t)
    {
        s[n]=0;
        for(int i=0;i<n;i++)
            s[i]*=t;
        for(int i=0;i<n;i++)
        {
            s[i+1]+=s[i]/D;
            s[i]%=D;
        }
        if(s[n])n++;
        return *this;
    }
    
};
const int N=1000000;
char num[256],tmp[N],x[N];
bigint sum,now;
main()
{
    int i,j,k,n,m,C=0;
    while(gets(tmp))
    {
        while(!tmp[0])
            if(!gets(tmp))return 0;
        sscanf(tmp,"%s",x);
        if(C++)puts("");
        for(n=0;x[n];n++)
            num[x[n]]=n;
        while(gets(tmp) && tmp[0])
        {
            sscanf(tmp,"%s",x);
            for(m=j=0;x[m];m++)
                j>?=(x[m]=num[x[m]])+1;
            sum=0;
            
            for(j>?=2;j<=n;j++)
            {
                now=0;
                for(k=0;k<m;k++)
                    (now*=j)+=x[k];
                //printf("%d %s\n",j,now.tostr());
                sum+=now;
            }
            printf("%s\n",sum.tostr());
        }
        
    }
}
