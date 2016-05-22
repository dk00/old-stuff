/*
ID: s0000151
PROG: frac1
LANG: C++
*/

#include<stdio.h>
#include<stdlib.h>
#define A1 *(long *)a
#define B1 *(long *)b
#define A2 (A1)%100000
#define B2 (B1)%100000
#define A3 ((A1)-(A2))/(A2)
#define B3 ((B1)-(B2))/(B2)
int numcmp(const void *a,const void *b){
    return (A3)-(B3);
}
main(){
freopen("frac1.in","r",stdin);
freopen("frac1.out","w",stdout);
long n,i,j,k,p,s[10000],pr[80],m;
pr[0]=2;pr[p=1]=3;
for(i=5,k=1;p<75;i++,k=1){
    for(j=1;k && pr[j]*pr[j]<=i;j++){
        if(i%pr[j]==0)k=0;
    }
    if(k)pr[++p]=i;
}
scanf("%ld",&n);
s[p=0]=1;       // 0/1
for(i=2;i<=n;i++){
    for(j=1;j<i;j++){
        m=1;
        for(k=0;m && pr[k]<=i && pr[k]<=j;k++){
            if(i%pr[k]==0 && j%pr[k]==0)m=0;
        }
        if(i%j==0 && j>1)m=0;
        if(m)s[++p]=j*100000+i;
    }
}
s[++p]=100001;   // 1/1
qsort((void *)s,p,sizeof(s[0]),numcmp);
for(i=0;i<=p;i++)printf("%ld/%ld\n",s[i]/100000,s[i]%100000);
//scanf(" ");
}
