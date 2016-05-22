#include<stdio.h>
int s[1000001];
main(){
int n,m,i,a,b;
scanf("%d",&n);
while(n--){
    scanf("%d",&m);
    s[0]=0;
    for(i=1;i<=m;i++){
        scanf("%d %d",&a,&b);
        s[i]=a+b;
    }
    for(i=m;i>0;i--)
        if(s[i]>=10){
            s[i-1]++;
            s[i]-=10;
        }
    if(s[0])printf("%d",s[0]);
    for(i=1;i<=m;i++)printf("%d",s[i]);
    puts("");
    if(n)puts("");
}
}
