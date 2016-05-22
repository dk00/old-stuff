/*
ID: s0000151
PROG: shopping
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
int s,b,min,on[99],ok[99][5],oc[99][5],op[99],bc[99],bk[99],bp[99],
k[1000],p[1000];char sp[100];
void buy(int pr,int y,int take){
    //printf("%d %05s\n",pr,itoa(take,sp,2));
    min<?=pr;
    int yn,i;
    for(;y<s;y++){
        for(yn=1,i=0;i<on[y];i++)
            yn=(yn && k[oc[y][i]]>=ok[y][i]);
        if(yn){
            for(i=0;i<on[y];i++){
                pr-=p[oc[y][i]]*ok[y][i];
                k[oc[y][i]]-=ok[y][i];
            }
            pr+=op[y];
            buy(pr,y,take|(1<<y));
            pr-=op[y];
            for(i=0;i<on[y];i++){
                k[oc[y][i]]+=ok[y][i];
                pr+=p[oc[y][i]]*ok[y][i];
            }
        }
    }
}
main(){
freopen("shopping.in","r",stdin);
freopen("shopping.out","w",stdout);
int i,j,sum=0;
scanf("%d",&s);
for(i=0;i<s;i++){
    scanf("%d",&on[i]);
    for(j=0;j<on[i];j++)
        scanf("%d %d",&oc[i][j],&ok[i][j]);
    scanf("%d",&op[i]);
}
scanf("%d",&b);
for(i=0;i<b;i++){
    scanf("%d %d %d",&bc[i],&bk[i],&bp[i]);
    k[bc[i]]+=bk[i];
    p[bc[i]]=bp[i];
    sum+=bp[i]*bk[i];
}
min=sum;
buy(sum,0,0);
printf("%d\n",min);
}
