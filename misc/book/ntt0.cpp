#include<algorithm>
using namespace std;
inline int pow(long long n,int k,int m){
    unsigned i;
    int a;
    for(a=i=1;i<=k;i*=2,n=(n*n)%m)
        if(k&i)a=(a*n)%m;
    return a;
}
inline int rev(int n,int k){
    int i=0;
    while(k--)(i<<=1)+=n&1,n/=2;
    return i;
}
const long long p=1107296257,r=10;
void ntt(bool f,int& n,int s[]){
    int i,j,k;
    long long x,w;
    for(j=1,k=0;j<n ;j<<=1,k++);
    for(;n<j;n++)s[n]=0;
    for(i=0;i<n;i++)
        if(i<rev(i,k))swap(s[i],s[rev(i,k)]);
    for(i=2;i<=n;i*=2){
        w=pow(pow(r,(p-1)/n,p),f?p-1-n/i:n/i,p);
        for(j=0;j<n;j+=i)
            for(k=0,x=1;k<i/2;k++){
                int &a=s[j+k],&b=s[j+k+i/2];
                b=(b*x)%p;
                a=(a*1ll+b)%p;
                b=(a+p+p-b-b)%p;
                x=x*w%p;
            }
    }
    x=pow(n,p-2,p);
    if(f)for(j=0;j<n;j++)
        s[j]=(s[j]*x)%p;
}
void mul(int n,int a[],int b[]){
    for(int i=0;i<n;i++)
        a[i]=(1ll*a[i]*b[i])%p;
}
void print(int n,int s[]){
    for(int i=0;i<n;i++)
        printf("%d ",s[i]);
    puts("");
}
