/*
ID: s0000151
PROG: barn1
LANG: C++
*/

#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
main(){
freopen("barn1.in","r",stdin);
freopen("barn1.out","w",stdout);
int m,s,c,i,j,st[201],ls[51],rs[51],max,p,sum,maxs;
scanf("%d %d %d",&m,&s,&c);
for(i=0;i<c;i++)scanf("%d",&st[i]);
qsort((void *)st,c,sizeof(st[0]),numcmp);
if(m>c){
    printf("%d\n",c);
    return 0;
}
ls[0]=0;rs[0]=c-1;
for(p=1;p<m;p++){
    for(max=0,i=0;i<p;i++){
        for(j=ls[i];j<rs[i];j++){
            if(st[j+1]-st[j]>st[max+1]-st[max]){
                max=j;maxs=i;
            }
        }
    }
    rs[p]=rs[maxs];rs[maxs]=max;ls[p]=max+1;
}
for(p--,sum=0;p>=0;p--)sum+=st[rs[p]]-st[ls[p]]+1;
printf("%d\n",sum);
//scanf(" ");
}
