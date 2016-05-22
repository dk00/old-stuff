#include<stdio.h>
main(){
long long nn;
long i,d,b1,b2,ton[256];
char num[12],digi[50],toa[]={"0123456789ABCDEF"};
for(i='0';i<='9';i++)ton[i]=i-'0';
for(i='A';i<='F';i++)ton[i]=i-'A'+10;
while(scanf("%d %d %s",&b1,&b2,&num)!=EOF){
    for(d=i=0;num[i];i++)if(ton[num[i]]>=b1)d=1;
    if(d){
        printf("%s is an illegal base %d number\n",num,b1);
        continue;
    }
    printf("%s base %d = ",num,b1);
    for(nn=i=0;num[i];i++)nn=nn*b1+ton[num[i]];
    for(i=0;nn>0;i++){
        digi[i]=toa[nn%b2];
        nn/=b2;
    }
    if(!i)printf("0");
    while(i--)printf("%c",digi[i]);
    printf(" base %d\n",b2);
}
}
