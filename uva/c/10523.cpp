#define Size 250
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#ifndef Size
#define Size 100
#endif
#ifndef D
#define D 1000000000
#endif
#ifndef Default
#define Default 0
#endif
class bigint{
public:
    long long num[Size];
    int d;
    bigint();
    void set(int n);
    char *tostr();
    void show();
    void carry();
    void uncarry();
    void trac();
    void operator=(bigint s);
    void operator=(long long s);
    void operator+=(bigint s);
    void operator-=(bigint s);
    void operator*=(long long s);
    bigint operator*(bigint s);
};
bigint::bigint(){
    num[d=0]=Default;
}
void bigint::set(int n){
    for(d++;d<n;d++)num[d]=0;
    num[n]=0;
}
char *bigint::tostr(){
    char *out=(char *)malloc(sizeof(char)*9*(d+1)),
         *tmp=(char *)malloc(sizeof(char)*9);
    sprintf(out,"%lld",num[d]);
    for(int i=d-1;i>=0;i--){
        sprintf(tmp,"%09lld",num[i]);
        strcat(out,tmp);
    }
    return out;
}
void bigint::show(){
    puts(tostr());
}
void bigint::carry(){
    for(int i=0;i<d;i++){
        if(num[i]>=D){
            num[i+1]+=num[i]/D;
            num[i]%=D;
        }
    }
    if(num[d]>=D){
        num[d+1]+=num[d]/D;
        num[d++]%=D;
    }
    trac();
}
void bigint::uncarry(){
    for(int i=d;i>0;i--){
        num[i]--;
        num[i-1]+=D;
    }
    if(num[d]<=0)d--;
}
void bigint::trac(){
    while(num[d]==0)d--;
}
void bigint::operator=(long long s){
    num[d=0]=s;
    carry();
}
void bigint::operator=(bigint s){
    for(d=0;d<=s.d;d++)num[d]=s.num[d];
    d=s.d;
    carry();
    while(num[d]==0)d--;
}
void bigint::operator+=(bigint s){
    if(d<s.d)set(s.d);
    else if(d>s.d)s.set(d);
    for(d=0;d<=s.d;d++)num[d]+=s.num[d];
    d--;
    carry();
}
void bigint::operator-=(bigint s){
    s.d>?=d;
    for(d=s.d;d>=0;d--){
        num[d]-=s.num[d];
        if(num[d]<0){
            num[d]+=D;
            num[d+1]--;
        }
    }
    d=s.d;
    trac();
}
void bigint::operator*=(long long s){
    for(int i=0;i<=d;i++)num[i]*=s;
    carry();
}
bigint bigint::operator*(bigint s){
    if(num[0]==1 && d==0)return s;
    if(s.num[0]==1 && s.d==0)return *this;
    bigint tmp;
    tmp.set(d+s.d+1);
    int i,j;
    for(i=0;i<=d;i++){
        for(j=0;j<=s.d;j++)
            tmp.num[i+j]+=num[i]*s.num[j];
        tmp.carry();
    }
    tmp.trac();
    return tmp;
}

bigint ans,pn,pr,tmp;
main(){
int i,n,a;
while(scanf("%d %d",&n,&a)){
    ans=0;
    pn=a;
    pr=pn;
    for(i=1;i<=n;i++,pn=pn*pr){
        tmp=i;
        ans+=pn*tmp;
    }
    ans.show();
}
}
