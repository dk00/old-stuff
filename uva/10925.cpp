#include<stdio.h>
#include<string.h>
#define Size 8
#define D 1000000000ll
char ___tmp[Size*10];
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
            bigint    (const int&    n){s[0]=n,d=1;}
            bigint    (const long long&n){s[0]=n,d=1;}
    bigint& operator= (const int&    n){s[0]=n%D;s[1]=n/D;d=s[1]?2:1;}
    bigint& operator= (const char   *c);
    bigint& operator+=(const bigint& n);
    bigint& operator/=(const int&    n);
    char*   tostr     (char    *c=NULL);
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
    d<?=Size;
    for(i=d;i<Size && i<=n.d;i++)s[i]=0;
    if(d<n.d)d=n.d;
    for(i=0;i<n.d && i<d;i++){
        s[i]+=n.s[i];
        if(s[i]>=D)
            s[i]-=D,s[i+1]++;
    }
    if(s[d]>0)d++;
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
main()
{
    int i,n,m,C=1;
    char tmp[1000];
    bigint s,sum;
    while(scanf("%d %d",&n,&m) && n+m)
    {
        for(sum=i=0;i<n;i++)
        {
            scanf("%s",tmp);
            s=tmp;
            sum+=s;
        }
        printf("Bill #%d costs %s: each friend should pay ",C++,sum.tostr());
        sum/=m;
        puts(sum.tostr());
        puts("");
    }
}
