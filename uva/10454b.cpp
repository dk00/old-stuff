#include<stdio.h>
#include<string.h>
#define Size 3
#define D 1000000000ll
char ___tmp[Size*10];
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){s[0]=n%D;s[1]=n/D;d=s[1]?2:1;}
    bigint& operator= (const char   *c);
    bigint& operator+=(const bigint& n);
//  bigint& operator-=(const bigint& n);
    bigint& operator*=(const int&    n);
    bigint  operator* (const bigint& n);
    bigint& operator*=(const bigint& b);
    bigint& operator/=(const int&    n);
    bool    operator< (const bigint& n);
    bool    operator<=(const bigint& n);
    bool    operator==(const bigint& n);
    char*   tostr     (char*    c=NULL);
};
bigint& bigint::operator=(const char *c){
    while(*c=='0' && c[1])c++;
int i,j=strlen(c);
    for(d=0;j>0;d++,j-=9)
        for(s[d]=0,i=j<9?0:j-9;i<j;i++)
            s[d]=s[d]*10+c[i]-'0';
    return *this;
}
char *bigint::tostr(char* c){
    if(c==NULL)
        c=___tmp;
int i,j;
    sprintf(c,"%lld",s[d-1]);
    j=strlen(c);
    for(i=d-2;i>=0;i--,j+=9)
        sprintf(c+j,"%09lld",s[i]);
    return c;
}
bigint& bigint::operator+=(const bigint& n){
int i;
    for(i=d;i<=n.d;i++)s[i]=0;
    if(d<n.d)d=n.d;
    for(i=0;i<d;i++){
        s[i]+=n.s[i];
        if(s[i]>=D)
            s[i]-=D,s[i+1]++;
    }
    if(s[d]>0)d++;
    return *this;
}
bigint& bigint::operator*=(const int& n){
int i;
    s[d]=0;
    for(i=0;i<d;i++)s[i]*=n;
    for(i=0;i<d;i++)
        if(s[i]>=D)
            s[i+1]+=s[i]/D,s[i]%=D;
    if(s[d]>0)d++;
    return *this;
}
bigint bigint::operator*(const bigint& b){
    bigint tmp;
    tmp=*this;
    tmp*=b;
    return tmp;
}
bigint& bigint::operator*=(const bigint& b){
bigint a=*this;
int i,j;
const long long *p=a.s,*q=(&b==this)?a.s:b.s;
    d=a.d+b.d;
    for(i=0;i<d;i++)s[i]=0;
    for(i=0;i<a.d;i++){
        for(j=0;j<b.d;j++)
            s[i+j]+=p[i]*q[j];
        for(j=0;j<d;j++)
            if(s[j]>=D)
                s[j+1]+=s[j]/D,s[j]%=D;
    }
    for(i=d-1;s[i]==0;i--);
    d=i+1;
    return *this;
}
bigint& bigint::operator/=(const int& n){
    for(int i=d-1;i>0;i--){
        s[i-1]+=(s[i]%n)*D;
        s[i]/=n;
    }
    s[0]/=n;
    while(d>1 && !s[d-1])d--;
    return *this;
}
bool bigint::operator<(const bigint& n){
    if(d<n.d)return true;
    if(d>n.d)return false;
    int i;
    for(i=d-1;i>0 && s[i]==n.s[i];i--);
    return(s[i]<n.s[i]);
}
bool bigint::operator<=(const bigint& n){
    if(d<n.d)return true;
    if(d>n.d)return false;
    int i;
    for(i=d-1;i>0 && s[i]==n.s[i];i--);
    return(s[i]<=n.s[i]);
}
bool bigint::operator==(const bigint& n){
    if(d-n.d)return false;
    int i;
    for(i=d-1;i>0 && s[i]==n.s[i];i--);
    return(s[i]==n.s[i]);
}

char s[200];
bigint one,zero,dp[200][200];
int u[200][200];
bigint calc(int st,int ed)
{
    if(u[st][ed])
        return dp[st][ed];
    if(st==ed)
    {
        if(s[st]>='0' && s[st]<='9')
            return one;
        else
            return zero;
    }
    int i,arc=0,star=1;
    if(s[st]=='(')
    {
        for(i=st+1,arc=1;arc && i<=ed;i++)
        {
            if(s[i]=='(')arc++;
            if(s[i]==')')arc--;
        }
        if(i>ed)return calc(st+1,ed-1);
    }
    for(i=st;star && i<=ed;i++)
    {
        if(s[i]=='(')arc++;
        if(s[i]==')')arc--;
        if(arc)continue;
        if(s[i]=='+')star=0;
    }
    for(int i=st;i<=ed;i++)
    {
        if(s[i]=='(')arc++;
        if(s[i]==')')arc--;
        if(arc)continue;
        if((star && s[i]=='*') || s[i]=='+')
            dp[st][ed]+=calc(st,i-1)*calc(i+1,ed);
    }
    u[st][ed]=1;
    return dp[st][ed];
}
main()
{
    int i,j;
    zero=0,one=1;
    while(scanf("%s",s)!=EOF)
    {
        for(i=0;s[i];i++)
            for(j=0;s[j];j++)
                dp[i][j]=0,u[i][j]=0;
        printf("%s\n",calc(0,i-1).tostr());
    }
}
