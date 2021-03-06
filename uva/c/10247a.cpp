#include<stdio.h>
#include<string.h>
#define Size 1020
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
    char*   tostring  (char*    c=NULL);
};
bigint& bigint::operator=(const char *c){
    while(*c=='0' && c[1])c++;
int i,j=strlen(c);
    for(d=0;j>0;d++,j-=9)
        for(s[d]=0,i=j<9?0:j-9;i<j;i++)
            s[d]=s[d]*10+c[i]-'0';
    return *this;
}
char *bigint::tostring(char* c){
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

bigint c[2][1200],s[22][22];
bool u[22][22];
int max(int a,int b){if(a>b)return a;return b;}
int exp(int n,int k)
{
    if(k==0)
        return 1;
    if(k%2)
        return n*exp(n,k-1);
    int tmp;
    tmp=exp(n,k/2);
    return tmp*tmp;
}
bigint &C(int n,int k)
{
    if(k>n-k)k=n-k;
    c[0][0]=1;
    int i,j,p;
    for(i=1;i<=k;i++)
    {
        c[0][i]=0;
        c[1][i]=0;
    }
    for(p=1,i=1;i<=n;i++,p=!p)
    {
        c[p][0]=1;
        for(j=1;j<=k;j++)
        
        {
            c[p][j]=0;
            c[p][j]+=c[!p][j];
            c[p][j]+=c[!p][j-1];
        }
    }
    return c[!p][k];
}
bigint &calc(int k,int d)
{
    if(u[k][d])
        return s[k][d];
    u[k][d]=1;
    s[k][d]=1;
    if(d<=0)
        return s[k][d];
    int i,n1=0,n2;
    for(i=1;i<=d;i++)
        n1+=exp(k,i);
    n2=n1/k;
    bigint p,q;
    p=calc(k,d-1);
    for(i=0;i<k;i++)
    {
        q=C(n1,n2);
        s[k][d]*=p;
        s[k][d]*=q;
        n1-=n2;
    }
    return s[k][d];
}
main()
{
    int k,d;
    while(scanf("%d %d",&k,&d)==2)
        printf("%s\n",calc(k,d).tostring());
}
