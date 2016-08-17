#include<cstdio>
#define lld "lld"
const int Size=1200;
const long long D=1000000000ll;
char __tmp[(Size+1)*9];
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
    bigint(const char a[])
    {
        int i;
        for(i=0;a[i];i++);
        for(n=0;(i-=9)>=0;n++)
            sscanf(a+i,"%9"lld,s+n);
        sprintf(__tmp,"%%%d"lld,9+i);
        if(i+9>0)sscanf(a,__tmp,s+n++);
        s[n]=0;
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
    bigint& operator-=(const bigint& t)
    {
        if(*this<t)return *this;
        for(int i=0;i<t.n;i++)
        {
            s[i]-=t.s[i];
            if(s[i]<0)s[i]+=D,s[i+1]--;
        }
        while(n>1 && !s[n-1])n--;
    }
    bool operator<(const bigint& t)const
    {
        if(n!=t.n)return n<t.n;
        for(int i=n-1;i>=0;i--)
            if(s[i]!=t.s[i])
                return s[i]<t.s[i];
        return 0;
    }
};
char tmp0[10001],tmp1[10001];
main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s %s",tmp0,tmp1);
        bigint a=tmp0,b=tmp1;
        if(a<b)
            b-=a,printf("-%s\n",(b).tostr());
        else
            a-=b,puts((a).tostr());
    }
}
