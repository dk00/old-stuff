#include<stdio.h>
main(){
int t,p,q,r,count;
freopen("03c.out","w",stdout);
scanf("%d",&t);
while(t--){
    scanf("%d %d",&p,&q);
    printf("%d/%d = ",p,q);
    printf("%d",p/q);
    p%=q;
    r=p,p=q,q=r;
    count=0;
    while(q && p%q){
        printf("+1/");
        if(q%(p%q))putchar('{'),count++;
        printf("%d",p/q);
        p%=q;
        r=p,p=q,q=r;
    }
    while(count--)printf("}");
    if(t)puts("");
}
}
