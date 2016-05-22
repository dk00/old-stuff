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
char s[10];int use[10]={0,0,0,0,0,0,0,0,0,0},
n,a1,a2,a3,b1,b2,c1,c2,c3,d1,d2,d3,e1,e2,e3,e4,p;
for(scanf("%d",&n);n--;){
    scanf("%d",&a1);
    use[a1]=1;
}
for(a1=1;a1<=9;a1++){
    if(!use[a1])continue;
    for(a2=1;a2<=9;a2++){
        if(!use[a2])continue;
        for(a3=1;a3<=9;a3++){
            if(!use[a3])continue;
            p=a1*100+a2*10+a3;
            for(b1=1;b1<=9 && p*b1<1000;b1++){
                if(!use[b1])continue;
                for(b2=1;b2<=9 && p*b2<1000 && p*b1*10+p*b2<10000;b2++){
                    if(!use[b2])continue;
                    c1=(p*b2)/100;
                    c2=((p*b2)%100)/10;
                    c3=(p*b2)%10;
                    d1=(p*b1)/100;
                    d2=((p*b1)%100)/10;
                    d3=(p*b1)%10;
                    e4=c3;
                    e3=(c2+d3)%10;
                    e2=(c1+d2+(c2+d3)/10)%10;
                    e1=d1+(c1+d2+(c2+d3)/10)/10;
                    printf("%5d%2d%2d\n",a1,a2,a3);
                    printf("x%6d%2d\n",b1,b2);
                    puts("----------");
                    printf("%5d%2d%2d\n",c1,c2,c3);
                    printf("%3d%2d%2d\n",d1,d2,d3);
                    puts("----------");
                    printf("%3d%2d%2d%2d\n",e1,e2,e3,e4);
                    gets(s);
                }
            }
        }
    }
}
if(DEBUG)scanf(" ");
}
