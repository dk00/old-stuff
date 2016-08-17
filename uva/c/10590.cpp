#include<stdio.h>
#include"bigint.h"
inline int abs(int a){return a>=0?a:-a;}
int s0[5000];
bigint s[5001];
main()
{
    int i,j;
    for(i=2;s0[i-3]<=5200;i++)
        s0[i-2]=i/2*(i/2*3*(i%2?-1:1)-1)/2*(((i-1)%4<2)?1:-1);
    for(s[0]=i=1;i<=5000;i++)
        for(j=0;abs(s0[j])<=i;j++)
            s[i]+=(s0[j]>0)?s[i-s0[j]]:-s[i+s0[j]];
    while(scanf("%d",&i)==1)
        printf("%s\n",s[i].tostr());
}
