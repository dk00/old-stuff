#include<stdio.h>
unsigned long long bit[64],s[10001],*r=&s[5000],use;
main(){
int i,j,n,m,max,min,psum,nsum,a[101],sum;
for(bit[0]=i=1;i<64;i++)bit[i]=(bit[i-1]<<1);
while(scanf("%d %d",&n,&m)!=EOF){
    min=10000000;max=-min;use=bit[n];
    for(psum=nsum=i=0;i<n+m;i++){
        scanf("%d",&a[i]);
        if(a[i]>=0)psum+=a[i];
        else nsum+=a[i];
    }
    for(i=nsum;i<=psum;i++)r[i]=0;
    r[0]=1;
    for(i=0;i<n+m;i++){
        if(a[i]>=0)
            for(j=psum;j>=nsum+a[i];j--)
                r[j]|=(r[j-a[i]]<<1);
        else
            for(j=nsum;j<=psum+a[i];j++)
                r[j]|=(r[j-a[i]]<<1);
    }
    sum=(nsum+psum);
    for(i=nsum;i<=psum;i++)
        if(r[i]&use){
            j=i*(sum-i);
            min<?=j;
            max>?=j;
        }
    printf("%d %d\n",max,min);
}
}
