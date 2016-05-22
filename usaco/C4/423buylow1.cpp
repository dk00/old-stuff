/*
PROG: buylow
ID: s0000151
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#define Size 20
#define D 1000000000ll
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){d=1,s[0]=n;}
    bigint& operator= (const char   *c);
    bigint& operator+=(const int&    n);
    bigint& operator+=(const bigint& n);
//  bigint& operator-=(const bigint& n);
    bigint& operator*=(const int&    n);
    bigint& operator*=(const bigint& b);
    char*   tostring  (char*         c);
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
int i,j;
    sprintf(c,"%lld",s[d-1]);
    j=strlen(c);
    for(i=d-2;i>=0;i--,j+=9)
        sprintf(c+j,"%09lld",s[i]);
    return c;
}
bigint& bigint::operator+=(const int& n){
    s[0]+=n;
    for(int i=0;s[i]>=D && i<d-1;i++)
        s[i]-=D,s[i+1]++;
    if(s[d-1]>=D)
        s[d-1]-=D,s[d++]=1;
    return *this;
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
bigint& bigint::operator*=(const bigint& b){
bigint a=*this;
int i,j;
const long long *p=a.s,*q=b.s;
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


bigint p[5000],sum;
int l[5000],s[5000];
main(){
freopen("buylow.in","r",stdin);
freopen("buylow.out","w",stdout);
int i,j,k,q,n,max=0;
char tmp[10000];
scanf("%d",&n);
for(i=0;i<n;i++)scanf("%d",&s[i]);
for(i=0;i<n;i++){
    for(j=k=0;j<i;j++)
        if(s[i]<s[j])k>?=l[j];
    l[i]=k+1;
    for(q=-1,j=i;j--;)
        if(s[i]<s[j] && s[j]!=q && l[j]==k)
            p[i]+=p[j],q=s[j];
    max>?=l[i];
    if(l[i]==1)p[i]=1;
}
for(q=-1,i=n;i--;)
    if(l[i]==max && s[i]!=q)
        sum+=p[i],q=s[i];
printf("%d %s\n",max,sum.tostring(tmp));
scanf("%s",tmp);
}
