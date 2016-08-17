#include<stdio.h>
double r,f,mean,s[50000];
main(){
int i,t,n,C=1,b;
scanf("%d",&t);
while(t-- && scanf("%d",&n)){
    b=n-1;
    for(r=1.0,i=1;i<n;i++){
        scanf("%lf",&s[i]);
        r*=i;
        while(r>1 && b--)r/=2;
        if(i<=n/2)r/=i;
        else r/=n-i;
    }
    scanf("%lf",&s[i]);
    while(b--)r/=2;
    mean=r*s[n/2+1];
    for(i=n/2,f=r;i>=1;i--){
        f*=i;
        f/=n-i;
        mean+=f*s[i];
    }
    for(i=n/2+2,f=r;i<=n;i++){
        f*=n-i+1;
        f/=i-1;
        mean+=f*s[i];
    }
    printf("Case #%d: %.3lf\n",C++,mean);
}
}

