#include<stdio.h>
main(){
int i,n,q,s[10001],C=1;
while(scanf("%d %d",&n,&q) && n+q){
    for(i=0;i<10001;i++)s[i]=0;
    while(n--){
        scanf("%d",&i);
        s[i]++;
    }
    for(i=1;i<10001;i++)s[i]+=s[i-1];
    printf("CASE# %d:\n",C++);
    while(q--){
        scanf("%d",&i);
        if(s[i]-(i?s[i-1]:0))
            printf("%d found at %d\n",i,i?s[i-1]+1:1);
        else printf("%d not found\n",i);
    }
}
}
