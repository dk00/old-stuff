#include<stdio.h>
main(){
int i,n,m;
while(scanf("%d %d",&n,&m)!=EOF){
    for(i=1;i<n && m>1;i*=m);
    if(n<m || i-n  || m==1){
        puts("Boring!");
        continue;
    }
    printf("%d",n);
    while(n>1){
        printf(" %d",n/=m);
    }
    puts("");
}
}
