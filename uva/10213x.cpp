#include<stdio.h>
#include<string.h>
#define Size 10
#define D 1000000000ll
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){d=1,s[0]=n%D;s[1]=n/D;if(s[1])d=2;}
    bigint& operator= (const char   *c);
    bigint& operator+=(const bigint& n);
//  bigint& operator-=(const bigint& n);
    bigint& operator*=(const int&    n);
    bigint& operator*=(const bigint& b);
    bigint& operator/=(const int&    n);
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
bigint& bigint::operator/=(const int&    n){
int i;
    for(i=d-1;i>0;i--){
        s[i-1]+=(s[i]%n)*D;
        s[i]/=n;
    }
    s[0]/=n;
    while(d>1 && !s[d-1])d--;
    return *this;
}
bigint a,b,one;
main(){
one=1;
int t,n;
char s[10000];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    a=n;
    (a*=(n-1))/=2;
    b=n;
    (((b*=(n-1))*=(n-2))*=(n-3))/=24;
    puts(((a+=b)+=one).tostring(s));
}
}
