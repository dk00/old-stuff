#include <stdio.h>
int n;
double prob[1000];
double calc(int k,int m){
    if(k==0) return 1.0;
    if(m==0) return 0.0;
    int i;
    double r,ans,p0,p;
    if(k!=1){
        ans=1.0;
        r=calc(1,m);
        while(k--)
            ans*=r;
    }
    else{
        ans=prob[0]*calc(0,m-1);
        p=p0=calc(1,m-1);
        for(i=1;i<n;i++,p*=p0)
            ans+=prob[i]*p;
    }
    return ans;
}
main(){
    int T,k,m,i,C=1;
    for(scanf("%d",&T);T>0;T--){
        scanf("%d %d %d",&n,&k,&m);
        for(i=0;i<n;i++)
            scanf("%lf",&prob[i]);
        printf("Case #%d: %.7lf\n",C++,calc(k,m));
    }
}
