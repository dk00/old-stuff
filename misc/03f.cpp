#include<stdio.h>
long long s[10001];
main(){
s[0]=1;
//freopen("f.out","w",stdout);
int i,k,n,p;
while(scanf("%d %d",&n,&p) && n+p){
    for(i=1;i<=p;i++)s[i]=0;
    while(n--){
        scanf("%d",&k);
        for(i=k;i<=p;i++)
            s[i]+=s[i-k];
    }
    printf("%lld\n",s[p]);
}
}
