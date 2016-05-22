#include<cstdio>
#define lld "lld" //change this into "lld" if using Linux.
const int Size=255;
const long long D=1000000000ll;
char __tmp[(Size+5)*9];
class bigint
{
    void fix(){
        s[n]=0;
        for(int i=0;i<n;i++)
            s[i+1]+=s[i]/D,s[i]%=D;
        if(s[n])n++;
        n<?=(Size/2-1);
        s[n]=0;
    }
public:
    int n;
    long long s[Size];
    bigint(const char a[])
    {
        int i;
        for(i=0;a[i];i++);
        for(n=0;(i-=9)>=0;n++)
            sscanf(a+i,"%9"lld,s+n);
        sprintf(__tmp,"%%%d"lld,9+i);
        if(i+9>0)sscanf(a,__tmp,s+n++);
        n<?=(Size/2-1);
        s[n]=0;
    }
    bigint(const long long &a){s[1]=a/D,s[0]=a%D,s[2]=0,n=1+!!s[1];}
    bigint(const int &a){*this=0ll+a;}
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
        {
            for(int j=0;j<t.n;j++)
                s[i+j]+=a[i]*b[j];
            for(int j=0;j<n;j++)
                s[j+1]+=s[j]/D,s[j]%=D;
        }
        while(n>1 && !s[n-1])n--;
        n<?=(Size/2-1);
        return *this;
    }
};
int n,m;
bigint c[51],x[51],p[51];
inline int strip(const char a[])
{
    //puts(a);
    int i,j,sum=0;
    for(i=0;a[i];i++);
    for(j=1;j<=m && j<=i;j++)
        sum+=(a[i-j]-'0')*(a[i-j]-'0');
    return sum;
}
inline int calc()
{
    bigint t,u=0;
    int i,sum=0;
    for(i=0;i<=n;i++)
    {
        t=x[i];
        u+=t*=c[i];
    }
    return strip(u.tostr());
}
int C[11][11];
char tmp[50005];
main()
{
    int i,j,k;
    bigint q;
    for(i=0;i<=10;i++)
        C[i][0]=1;
    for(i=1;i<=10;i++)
        for(j=1;j<=i;j++)
            C[i][j]=C[i-1][j-1]+C[i-1][j];
    while(scanf("%d %s %d %d",&n,tmp,&k,&m)==4)
    {
        x[1]=tmp;
        x[0]=1;
        for(i=2;i<=n;i++)
        {
            x[i]=x[i-1];
            x[i]*=x[1];
        }
        for(i=n;i>=0;i--)
        {
            scanf("%s",tmp);
            c[i]=tmp;
        }
        while(k--)
        {
            printf("%d\n",calc());
            for(i=0;i<=n;i++)
                p[i]=x[i];
            for(i=1;i<=n;i++)
                for(j=0;j<i;j++)
                {
                    q=p[j];
                    q*=C[i][j];
                    x[i]+=q;
                }
        }
    }
    return 0;
}
