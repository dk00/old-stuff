#include<stdio.h>
main(){
int i,n,t;
double a0,a1,an1,c[5000];
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    scanf("%lf %lf",&a0,&an1);
    for(i=1;i<=n;i++)scanf("%lf",&c[i]);
    a1=n*a0+an1;
    for(i=0;i<n;i++)a1-=2*(n-i)*c[i+1];
    a1/=(n+1);
    printf("%.2lf\n",a1);
    if(t)puts("");
}
}
//(n+1)a1=n*a0 + (an+1) - 2(n*c1 + (n-1)*c2 + (n-2)*c3 + ... + 1*cn)
