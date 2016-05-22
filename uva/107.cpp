#include<stdio.h>
main(){
long long h,c,n,i,j;
while(scanf("%I64d %I64d",&h,&c) && (h || c)){
    if(c==0){
        printf("1 %I64d\n",h);
        continue;
    }
    for(n=1;c>1;n++){
        if(h%(n+1)==0 && c%n==0){
            for(i=h,j=c;i>1 && j>1;i/=(n+1),j/=n);
            if(i==1 && j==1)break;
        }
    }
    for(i=h,c=h=0,j=1;i>1;){
        h+=i*j;
        c+=j;
        i/=n+1;
        j*=n;
    }
    printf("%I64d %I64d\n",c,h+j);
}
}
