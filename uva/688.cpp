#include<stdio.h>
int s[100];
main(){
int i,j,k,n,t;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(k=0,i=2;k+i<=n;k+=i++)
        s[i-2]=i;
    for((--i+=j=--i)+=j;k<n;k++)
        s[--i%j]++;
    for(i=0;i<j;i++)printf("%d%c",s[i],(i+1-j)?' ':'\n');
}
}
