#include<stdio.h>
main(){
int i,j,k,t,c,r,C=1,s1[10000],s2[10000];
scanf("%d",&t);
while(t--){
    scanf("%d %d",&c,&r);
    printf("Case #%d:",C++);
    if(c-r);
    else{
        puts(" 0");
        continue;
    }
    c-=r;
    for(j=k=0,i=1;i*i<c;i++)
        if(!(c%i)){
            s1[j++]=i;
            s2[k++]=c/i;
        }
    if(i*i==c && i>r)s1[j++]=i;
    for(i=0;i<j && s1[i]<=r;i++);
    for(;i<j;i++)printf(" %d",s1[i]);
    while(k--){
        if(s2[k]<=r)continue;
        printf(" %d",s2[k]);
    }
    puts("");
}
}
