#include<stdio.h>
main(){
int i,s[300],max,start,n,k;
while(scanf("%d",&n) && n){
    for(max=i=0;i<n;i++)
        scanf("%d",&s[i]);
    for(i=1;i<n;i++){
        for(k=0;s[i]-s[i-1]<=5;k++,i++);
        if(k>max){
            start=i-k-1;
            max=k;
        }
    }
    for(i=start;i<=start+max;i++)printf("%d ",s[i]);
    puts("");
}
}
