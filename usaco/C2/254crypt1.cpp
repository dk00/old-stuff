/*
ID: s0000151
PROG: crypt1
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
main(){
if(!DEBUG){freopen("crypt1.in","r",stdin);
freopen("crypt1.out","w",stdout);}
char s[10];int use[10]={0,0,0,0,0,0,0,0,0,0},p[10]={0,0,1,1,0,1,0,1,0,0}
,n,a1,a2,a3,b1,b2,c1,c2,c3,d1,d2,d3,e1,e2,e3,e4,q,n5;
for(scanf("%d",&n),n5=n>7?9:0;n--;){
    scanf("%d",&a1);
    use[a1]=1;
}
for(a1=1;a1<=9;a1++){
    if(!use[a1])continue;
    for(a2=1;a2<=9;a2++){
        if(!use[a2])continue;
        for(a3=1;a3<=9;a3++){
            if(!use[a3])continue;
            q=a1*100+a2*10+a3;
            for(b1=1;b1<=9 && q*b1<1000;b1++){
                if(!use[b1])continue;
                for(b2=1;b2<=9 && q*b2<1000 && q*(b1*10+b2)<10000;b2++){
                    if(!use[b2])continue;
                    c1=(q*b2)/100;
                    c2=((q*b2)%100)/10;
                    c3=(q*b2)%10;
                    d1=(q*b1)/100;
                    d2=((q*b1)%100)/10;
                    d3=(q*b1)%10;
                    e4=c3;
                    e3=(c2+d3)%10;
                    e2=(c1+d2+(c2+d3)/10)%10;
                    e1=d1+(c1+d2+(c2+d3)/10)/10;
                    if(use[c1]+use[c2]+use[c3]+use[d1]+use[d2]+use[d3]+
                    use[e1]+use[e2]+use[e3]+use[e4]==10 && p[b1]+p[b2]
                    +p[a1]+p[a2]+p[a3]+p[c1]+p[c2]+p[c3]+p[d1]+p[d2]+
                    p[d3]+p[e1]+p[e2]+p[e3]+p[e4]>0)n5++;
                }
            }
        }
    }
}
printf("%d\n",n5);
if(DEBUG)scanf(" ");
}
