#include<stdio.h>
#include<string.h>
#define Size 500
#define D 1000000000ll
class bigint{
public:
long long d,s[Size];
           bigint    (               ){d=1,s[0]=0;}
   bigint& operator= (const int&    n){d=1,s[0]=n;}
   bigint& operator= (const bigint& n);
   bigint& operator= (const char   *c);
   bigint& operator+=(const int&    n);
   bigint& operator+=(const bigint& n);
//  bigint& operator-=(const bigint& n);
   bigint& operator*=(const int&    n);
   bigint& operator* (const bigint& n)const;
   char*   tostring  (char*         c);
};
bigint& bigint::operator=(const bigint& n){
   for(d=0;d<n.d;d++)s[d]=n.s[d];
   return *this;
}
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
#define DEBUG 1
int s[5000],l[5000];
bigint p[5000],maxs;
main(){
if(!DEBUG){freopen("buylow.in","r",stdin);
freopen("buylow.out","w",stdout);}
int i,j,k,n,maxl=0;
char tmp[10000];
scanf("%d",&n);
for(i=0;i<n;i++)scanf("%d",&s[i]);
l[0]=1;
p[0]=1;
for(i=1;i,n;i++){
    for(k=j=0;j<i;j++)
        if(s[i]<=s[j] && l[j]>k)k=l[j];
    l[i]=k+1;
    for(j=0;j<i;j++)
        if(l[j]==k)
            p[i]+=p[j];
    if(maxl<=l[i])
        maxl=l[i],maxs=p[i];
}
printf("%d %s\n",maxl,maxs.tostring(tmp));
if(DEBUG)scanf(" ");
}
