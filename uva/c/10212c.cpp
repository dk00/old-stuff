#include<stdio.h>
long f[10];
void last(long n,long m){
    if(!m)return;
    for(;n%10!=0 && m;n--,m--)f[n%10]++;
    f[0]+=m/10;f[1]+=m/10;f[2]+=m/10;f[3]+=m/10;f[4]+=m/10;
    f[5]+=m/10;f[6]+=m/10;f[7]+=m/10;f[8]+=m/10;f[9]+=m/10;
    last(n/10,m/10+(m%10>0));
    for(m%=10;m;n--,m--)
        f[n%10]++;
}
main(){
    long m,n,p;
    while(scanf("%ld %ld",&n,&m)!=EOF){
        f[0]=f[1]=f[2]=f[3]=f[4]=f[5]=f[6]=f[7]=f[8]=f[9]=0;
        last(n,m);
        f[2]+=f[4]*2+f[8]*3+f[6];
        f[3]+=f[6]+f[9]*2;
        if(f[5]<f[2]){f[2]-=f[5];f[5]=0;}
        if(f[2]>0)f[2]=f[2]%4+(f[2]%4==0)*4;
        f[3]%=4;f[7]%=4;
        for(p=1;f[7]>0;f[7]--)p=(p*7)%10;
        for(;f[3]>0;f[3]--)p=(p*3)%10;
        for(;f[5]>0;f[5]--)p=(p*5)%10;
        for(;f[2]>0;f[2]--)p=(p*2);
        while(p%10==0)p/=10;
        printf("%ld\n",p%10);
    }
}
