#include<stdio.h>
double rate[3][5]={{0.10,0.25,0.53,0.87,1.44},{0.06,0.15,0.33,0.47,0.80},
{0.02,0.05,0.13,0.17,0.30}};
main(){
int h1,h2,m1,m2,day,eve,nit;
char c,s[100],num[100];
while(scanf("%s",s) && *s-'#'){
    c=*s;
    scanf("%s %d %d %d %d",num,&h1,&m1,&h2,&m2);
    day=eve=nit=0;
    for(;h1!=h2;h1++,h1%=24,m1=0)
        for(;m1<60;m1++)
            if(h1>=8 && h1<18)day++;
            else if(h1>=18 && h1<22)eve++;
            else nit++;
    for(;m1<m2;m1++)
        if(h1>=8 && h1<18)day++;
        else if(h1>=18 && h1<22)eve++;
        else nit++;
    printf("%-10s%-6d%-6d%-6d%-3s%8.2lf\n",num,day,eve,nit,s,
    day*rate[0][c-'A']+eve*rate[1][c-'A']+nit*rate[2][c-'A']);
}
}
