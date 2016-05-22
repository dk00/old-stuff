#include<stdio.h>
main(){
int i,a,n,p,m;
while(scanf("%d %d %d",&n,&p,&m)!=EOF){
    for(n%=m,i=a=1;i<=p && i>0;i<<=1,n=(n*n)%m)
        if(p&i)a=(a*n)%m;
    printf("%d\n",a);
}
}
