/*
ID: s0000151
PROG: milk
LANG: C++
*/

#include<stdio.h>
main(){
freopen("milk.in","r",stdin);
freopen("milk.out","w",stdout);
long n,m,i,j,p[5001],a[5001],temp,k;
scanf("%ld %ld",&n,&m);
for(i=0;i<m;i++){
    scanf("%ld %ld",&p[i],&a[i]);
    for(j=i-1;j>=0 && p[j]>p[j+1];j--){
        temp=p[j];p[j]=p[j+1];p[j+1]=temp;
        temp=a[j];a[j]=a[j+1];a[j+1]=temp;
    }
}
for(i=0,k=0;i<m && n>0;i++){
    if(a[i]<=n){
        k+=a[i]*p[i];
        n-=a[i];
    }
    else{
        k+=n*p[i];
        break;
    }
}
printf("%ld\n",k);
//scanf(" ");
}
