#include<stdio.h>
main(){
int i,j,k,p,n,op[101];
while(scanf("%d",&n) && n){
    for(i=1;;i++){
        if(i%n==13)continue;
        for(j=0;j<n;j++)op[j]=j+1;
        op[0]=0;
        for(k=n-1,j=-1;k>1;k--){
            p=i%k;
            if(!p)p+=k;
            p=p;
            while(p--)for(j++;!op[j%n];j++);
            op[j%=n]=0;
        }
        if(op[12])break;
    }
    printf("%d\n",i);
}
}
