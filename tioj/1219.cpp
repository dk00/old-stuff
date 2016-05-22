#include<cstdio>
unsigned i,j,a,b,c,s[50001];
main(){
    while(scanf("%u%u%u",&a,&b,&c)&&a+b+c){
        a/=c,b/=c,c=a<?b;
        for(i=c;i>0;i--)
            for(s[i]=(a/i)*(b/i),j=i*2;j<=c;j+=i)
                s[i]-=s[j];
        printf("%u\n",s[1]);
    }
}
