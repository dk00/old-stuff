/* @JUDGE_ID:  58589NF  530  C++  ""*/
#include<stdio.h>
#include<malloc.h>
int main(){
long n,m,i,j,*c[2343];
c[3]=(long *)malloc(sizeof(long)*2343);
c[3][0]=1;
for(i=1;i<=2341;i+=2){
    c[3][i]=c[3][i-1]+(i+2)*((i+1)/2);
    c[3][i+1]=c[3][i]+((i+3)/2)*(i+2);
}
for(i=4;i<=2341;i++){
    c[i]=(long *)malloc(sizeof(long)*2343-i);
    c[i][0]=1;
    for(j=1;j<=2343-i;j++)
        c[i][j]=c[i-1][j]+c[i][j-1];
}
while(1){
    scanf("%ld %ld",&n,&m);
    if(n==0 && m==0)break;
    if(m==0 || n-m==0){
        printf("1\n");
        continue;
    }
    if(m==1 || n-m==1){
        printf("%ld\n",n);
        continue;
    }
    if(m==2 || n-m==2){
        printf("%ld\n",--n%2==1?n*((n+1)/2):(n/2)*(n+1));
        continue;
    }
    if(n-m<m) printf("%ld\n",c[n-m][m]);
    else printf("%ld\n",c[m][n-m]);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
