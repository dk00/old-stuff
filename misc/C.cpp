#include<stdio.h>
main(){
    int n,m,i,flag;
    int a[1001];
    while(1){
        scanf("%d %d",&n,&m);
        if(n==0 && m==0)
            break;
        for(i=0;i<n;i++)
            scanf("%d",&a[i]);
        flag=0;
        if(m%2==0){
            for(i=0;i<n && a[i]%2==0;i++);
        }
        if(i==n)
            flag=1;
        if(m%3==0){
            for(i=0;i<n && a[i]%3==0;i++);
        }
        if(i==n)
            flag=1;
        if(m%5==0){
            for(i=0;i<n && a[i]%5==0;i++);
        }
        if(i==n)
            flag=1;
        if(m%7==0){
            for(i=0;i<n && a[i]%7==0;i++);
        }
        if(i==n)
            flag=1;        
    }
}
