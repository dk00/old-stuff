#include<stdio.h>
#include<string.h>
#define Size 12
#define D 1000000000ll
char ___tmp[Size*10];
class bigint{
public:
long long d,s[Size];
            bigint    (               ){d=1,s[0]=0;}
    bigint& operator= (const int&    n){s[0]=n%D;s[1]=n/D;d=s[1]?2:1;}
    bigint& operator+=(const bigint& n);
    char*   tostring  (char*    c=NULL);
};
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

bigint s[101];
char s1[10001],s2[101];
main()
{
    int i,j,n,t;
    s[0]=1;
    scanf("%d%c",&t,s1);
    while(t--)
    {
        gets(s1+1),gets(s2+1);
        for(n=1;s2[n];n++)
            s[n]=0;
        for(i=1;s1[i];i++)
            for(j=n-1;j>0;j--)
                if(s1[i]==s2[j])
                    s[j]+=s[j-1];
        printf("%s\n",s[n-1].tostring());
    }
}
