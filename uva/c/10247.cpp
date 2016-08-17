#include<stdio.h>
#include<string.h>
#define Size 1070
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
    bigint& operator-=(const bigint& n);
    bigint& operator*=(const bigint& b);
    bigint  operator+ (const bigint& n);
    bigint  operator- (const bigint& n);
    bigint  operator* (const bigint& n);
    bigint& operator/=(const int&    n);
    bool    operator< (const bigint& n);
    bool    operator<=(const bigint& n);
    bool    operator==(const bigint& n);
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
bigint bigint::operator+(const bigint& b){
    bigint tmp;
    tmp=*this;
    tmp+=b;
    return tmp;
}
bigint bigint::operator-(const bigint& b){
    bigint tmp;
    tmp=*this;
    tmp-=b;
    return tmp;
}
bigint bigint::operator*(const bigint& b){
    bigint tmp;
    tmp=*this;
    tmp*=b;
    return tmp;
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
bigint& bigint::operator-=(const bigint& n){
int i;
    for(i=d;i<=n.d;i++)s[i]=0;
    if(d<n.d)d=n.d;
    for(i=((d<?n.d)-1);i>=0;i--){
        s[i]-=n.s[i];
        if(s[i]<0)
            s[i]+=D,s[i+1]--;
    }
    if(s[d-1]<=0)d--;
    return *this;
}
bigint& bigint::operator*=(const bigint& b){
bigint a=*this;
int i,j;
const long long *p=a.s,*q=(&b==this)?a.s:b.s;
    d=a.d+b.d;
    for(i=0;i<=d;i++)s[i]=0;
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

bool notp[3280];
int p[1000],s[1000];
char *ans[22][22];
bigint pow(bigint n,int k)
{
    if(!k)return 1;
    if(k%2)return pow(n,k-1)*n;
    n=pow(n,k/2);
    return n*n;
}
char tmp[10900];
main()
{
    int i,j,k,l,m,n,pn,num;
    bigint sum;
    pn=1,p[0]=2;
    for(i=3;i<3290;i++,i++)
    {
        if(notp[i])continue;
        for(j=i*i;j<3280;j+=i*2)
            notp[j]=1;
        p[pn++]=i;
    }
    for(k=1;k<=21;k++)for(n=1;n*k<=21;n++)
    {
        for(i=0;i<pn;i++)s[i]=0;
        for(i=num=0,j=1;i<=n;i++,j*=k)
            num+=j;
        for(i=0;p[i]<=num;i++)
            for(s[i]=0,j=num;j>1;s[i]+=j/=p[i]);
        for(i=0,j=1;i<=n;i++,j*=k)
        {
            m=num;
            for(l=0;p[l]<=m;l++)
                while(m%p[l]==0)m/=p[l],s[l]-=j;
            num=(num-1)/k;
        }
        for(i=0,sum=1;i<pn;i++)
            sum*=pow(p[i],s[i]);
        strcpy(tmp,sum.tostr());
        ans[k][n]=new char[strlen(tmp)+1];
        strcpy(ans[k][n],tmp);
        printf("ans[%d][%d]=new char[%d];",k,n,strlen(tmp)+1);
        printf("strcpy(ans[%d][%d],\"%s\");\n",k,n,tmp);
    }
    while(scanf("%d %d",&k,&n)==2)
        puts(ans[k][n]);
}
