#include<stdio.h>
int a[16],f[10000];
main(){
int i,j,d,n,m;
freopen("10870.in","r",stdin);
freopen("10870b.out","w",stdout);
while(scanf("%d %d %d",&d,&n,&m) && n+d+m){
    for(i=1;i<=d;i++){
        scanf("%d",&a[i]);
        a[i]%=m;
    }
    for(i=1;i<=d;i++){
        scanf("%d",&f[i]);
        f[i]%=m;
    }
    for(i=d+1;i<=n;i++)
        for(f[i]=0,j=1;j<=d;j++)
            f[i]=(f[i]+(f[i-j]*a[j])%m)%m;
    printf("%d\n",f[n]);
}
}
