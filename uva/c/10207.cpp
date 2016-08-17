#include<cstdlib>
#include<stdio.h>
#include<string.h>
#define Size 70
#define D 1000000000ll
char ___tmp[Size*10];
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){s[0]=n%D;s[1]=n/D;d=s[1]?2:1;}
    bigint& operator= (const char   *c);
    bigint& operator+=(const bigint& n);
    bigint& operator-=(      bigint& a);
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
    for(i=s[d]=0;i<n.d;i++){
        s[i]+=n.s[i];
        if(s[i]>=D)
            s[i]-=D,s[i+1]++;
    }
    if(s[d]>0)d++;
    return *this;
}
bigint& bigint::operator-=(bigint& a)
{
    for(int i=s[d]=0;i<a.d;i++)
    {
        s[i]-=a.s[i];
        if(s[i]<0)
            s[i]+=D,s[i+1]--;
    }
    while(d>1 && s[d-1]==0)d--;
    s[d]=0;
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
    s[d=a.d+b.d]=0;
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

struct data
{
    int i,j,n;
    double a1;
    bigint a2;
}test[1000];
int cmp1(const void *a,const void *b)
{
    if(((data *)a)->i!=((data *)b)->i)
        return ((data *)a)->i-((data *)b)->i;
    return ((data *)a)->j-((data *)b)->j;
}
int cmp2(const void *a,const void *b)
{
    return ((data *)a)->n-((data *)b)->n;
}
bigint s[1001],two;
double P[1001];
main()
{
    two=2;
    int i,j,k,n,maxi,maxj,C=0;
    double p;
    while(scanf("%lf %d",&p,&n)==2)
    {
        maxi=maxj=0;
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&test[i].i,&test[i].j);
            maxi>?=test[i].i,maxj>?=test[i].j;
            test[i].n=i;
        }
        qsort(test,n,sizeof(test[0]),cmp1);
        for(j=0;j<=1000;j++)
            P[j]=1.0,s[j]=0;
        for(i=k=0;i<=maxi;i++)
        {
            if(i)
                for(j=1;j<=maxj;j++)
                    s[j]+=s[j-1],s[j]+=two,P[j]=p*P[j]+(1-p)*P[j-1];
            for(j=0;j<=1000;j++)
            {
                while(test[k].i<i || (test[k].i==i&&test[k].j<j))k++;
                while(i==test[k].i && j==test[k].j)
                    test[k].a1=P[j],test[k++].a2=s[j];
            }
            P[0]=0;
        }
        qsort(test,n,sizeof(test[0]),cmp2);
        for(i=0;i<n;i++)
        {
            if(test[i].i>1000 || test[i].j>1000 ||
            test[i].i<0 || test[i].j<0 || test[i].i==0 && test[i].j==0)
                puts("-1.00000\n0");
            else
                printf("%.5lf\n%s\n",
                test[i].a1,test[i].a2.tostring());
        }
        puts("");
    }
}
