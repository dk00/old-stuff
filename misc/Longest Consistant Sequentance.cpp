#include<stdio.h>
main(){
int i,s[300],max,start,n,k;
while(scanf("%d",&n) && n){
    for(max=i=0;i<n;i++){
        scanf("%d",&s[i]);
        for(k=i;i && s[i]==s[i]-1 && i<n;i++)scanf("%d",&s[i]);
        if(k-i>max){
            start=k;
            max=k-i;
        }
    }
    for(i=start;i<start+max;i++)printf("%d ",s[i]);
    puts("");
}
}
