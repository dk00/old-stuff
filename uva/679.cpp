#include<stdio.h>
main(){
int i,s,d,t;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&d,&i);
    for(s=1,i--;d-->1;i>>=1)
        s=(s<<1)|(i&1);
    printf("%d\n",s);
}
}
