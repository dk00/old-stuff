/*
ID: s0000151
PROG: crypt1
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
main(){
if(!DEBUG){freopen("crypt1.in","r",stdin);
freopen("crypt1.out","w",stdout);}
int i,n,f,a1,a2,a3,b1,b2,c1,c2,c3,d1,d2,d3,f1,f2,f3,f4,use[10],p;
scanf("%d",&n);
for(i=0;i<n;i++)scanf("%d",&use[i]);
for(a1=0;a1<n;a1++){
    for(a2=0;a2<n;a2++){
        for(a3=0;a3<n;a3++){
            p=use[a1]*100+use[a2]*10+use[a3];
            for(b1=0;b1<n && p*use[b1]*10<10000;b1++){
                for(b2=0;b2<n && p*(use[b1]*10+use[b2])<10000;b2++){
                    c1=p*use[b1]/100;
                    c2=((p*use[b1])%100)/10;
                    c3=(p*use[b1])%10;
                    d1=p*use[b2]/100;
                    d2=((p*use[b2])%100)/10;
                    d3=(p*use[b2])%10;
                    f4=c3;
                    f3=c2+d3;
                    f2=c1+d2;
                    f1=d1;
                    printf("%5d%2d%2d\n",use[a1],use[a2],use[a3]);
                    printf("x%6d%2d\n",use[b1],use[b2]);
                    puts("--------------");
                    printf("%5d%2d%2d\n",c1,c2,c3);
                    printf("%3d%2d%2d\n",d1,d2,d3);
                    puts("--------------");
                    printf("%3d%2d%2d%2d\n",f1,f2,f3,f4);
                    scanf("%d",&i);
                }
            }
        }
    }
}
if(DEBUG)scanf(" ");
}
