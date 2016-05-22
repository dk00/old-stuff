#include<stdio.h>
int s[500],p[500],b[500];
main(){
int i,j,k,t,n,m,num,sum,con,min,max;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&n,&m);
    for(i=j=k=0;i<n;k+=s[i++])
        scanf("%d",&s[i]),j>?=s[i];
    min=100000000;
    while(j<=k){
        max=(j+k)/2;
        for(i=num=sum=0,con=1;i<n && con<=m;i++){
            p[i]=0;
            if(con==m){
                sum+=s[i];
                continue;
            }
            if(sum && sum+s[i]>max){
                num>?=sum;
                sum=0;
                con++;
                p[i-1]=1;
            }
            sum+=s[i];
        }
        num>?=sum;
        if(con==m && num<min){
            min=num;
            for(i=0;i<n;i++)
                b[i]=p[i];
        }
        if(sum>max)j=max+1;
        else k=max-1;
    }
    printf("%d",s[0]);
    if(b[0])printf(" /");
    for(i=1;i<n;i++){
        printf(" %d",s[i]);
        if(b[i])printf(" /");
    }
    puts("");
}
}
