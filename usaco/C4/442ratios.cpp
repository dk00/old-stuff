/*
ID: s0000151
PROG: ratios
LANG: C++
*/
#include<stdio.h>
main(){
freopen("ratios.in","r",stdin);
freopen("ratios.out","w",stdout);
int i,j,k,l,a1,a2,a3,b1,b2,b3,c1,c2,c3,s1,s2,s3,r1,r2,r3,rate;
scanf("%d %d %d",&s1,&s2,&s3);
scanf("%d %d %d",&a1,&a2,&a3);
scanf("%d %d %d",&b1,&b2,&b3);
scanf("%d %d %d",&c1,&c2,&c3);
for(i=0;i<=100;i++)
    for(j=0;j<=100;j++)
        for(k=0;k<=100;k++){
            r1=a1*i+b1*j+c1*k;
            r2=a2*i+b2*j+c2*k;
            r3=a3*i+b3*j+c3*k;
            if((!s1 && r1)+(!s2 && r2)+(!s3 && r3))continue;
            if((s1 && !r1)+(s2 && !r2)+(s3 && !r3))continue;
            if((s1 && r1%s1)+(s2 && r2%s2)+(s3 && r3%s3))continue;
            rate=(r1/(s1?s1:1))>?(r2/(s2?s2:1))>?(r3/(s3?s3:1));
            if(!(s1*rate-r1 || s2*rate-r2 || s3*rate-r3)){
                printf("%d %d %d %d\n",i,j,k,rate);
                return 0;
            }
        }
puts("NONE");
}
