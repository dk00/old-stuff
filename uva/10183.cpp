#include"bigintA03.h"
bigint a,b,f[501],max,r,one;
char c[10000],s1[10000],s2[10000];
main(){
int i,j,st,ed;
one=1;
max=1,r=10;
for(i=1;i<100;i<<=1,r*=r)
    if(100&i)
        max*=r;
f[0]=1,f[1]=1;
for(i=2;i<=500;i++){
    f[i]=0;
    (f[i]+=f[i-1])+=f[i-2];
}
one=1;
while(scanf("%s %s",s1,s2)){
    a=s1,b=s2;
    if(a<one && b<one)break;
    for(st=1,ed=500;st<=ed;){
        i=(st+ed)/2;
        if((i<=0 || f[i-1]<a) && a<=f[i])break;
        else if(f[i]<a)st=i+1;
        else ed=i-1;
    }
    for(st=1,ed=500;st<=ed;){
        j=(st+ed)/2;
        if((j<=0 || f[j-1]<=b) && b<f[j])break;
        else if(f[j]<=b)st=j+1;
        else ed=j-1;
    }
    printf("%d\n",j-i);
}
}
