#include<stdio.h>
#include<string.h>
#define Size 300
#define D 1000000000ll
char ___tmp[Size*10];
class bigint
{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){s[0]=n%D;s[1]=n/D;d=s[1]?2:1;}
    bigint& operator*=(const int&    n);
    char*   tostring  (char*    c=NULL);
};
char *bigint::tostring(char* c)
{
    if(c==NULL)
        c=___tmp;
int i,j;
    sprintf(c,"%lld",s[d-1]);
    j=strlen(c);
    for(i=d-2;i>=0;i--,j+=9)
        sprintf(c+j,"%09lld",s[i]);
    return c;
}
bigint& bigint::operator*=(const int& n)
{
int i;
    s[d]=0;
    for(i=0;i<d;i++)s[i]*=n;
    for(i=0;i<d;i++)
        if(s[i]>=D)
            s[i+1]+=s[i]/D,s[i]%=D;
    if(s[d]>0)d++;
    return *this;
}
bigint fact[1001];
main()
{
    int i;
    fact[0]=1;
    for(i=1;i<=1000;i++)
    {
        fact[i]=fact[i-1];
        fact[i]*=i;
    }
    while(scanf("%d",&i)!=EOF)
        printf("%d!\n%s\n",i,fact[i].tostring());
}
