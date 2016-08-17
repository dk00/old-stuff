#include<stdio.h>
int f[100001],x10[]={1,10,100,1000,10000};
main(){
int i,t,a,b,n,m;
scanf("%d",&t);
while(t--){
    scanf("%d %d %d %d",&a,&b,&n,&m);
    m=x10[m];
    f[0]=(a%=m),f[1]=(b%=m);
    for(i=2;;i++){
        f[i]=(f[i-1]+f[i-2])%m;
        if(f[i]==b && f[i-1]==a)break;
    }
    i--;
    printf("%d\n",f[n%i]);
}
}
