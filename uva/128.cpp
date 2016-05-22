#include<stdio.h>
#include<string.h>
main(){
char mes[1025];
long i,n,rr;
long long r;
while(gets(mes) && mes[0]!='#'){
    n=strlen(mes);
    if(n%2){
        for(i=n++;i>0;i--)mes[i]=mes[i-1];
        mes[0]=0;
    }
    for(r=i=0;i<n;i+=2){
        r+=(mes[i]<<8)+mes[i+1];
        r%=34943;
        r<<=16;
    }
    r%=34943;
    rr=(34943-r)%34943;
    printf("%02X %02X\n",rr>>8,rr%256);
}
}
