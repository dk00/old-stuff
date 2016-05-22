/*
ID: s0000151
PROG: milk4
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
int dp[20001],num[20001],use[20001],pu[10001],px[100];
int numcmp(const void *a,const void *b){return *(int *)b-*(int *)a;}
main(){
freopen("milk4.in","r",stdin);
freopen("milk4.out","w",stdout);
int i,k,q,p,pv;
scanf("%d %d",&q,&p);
dp[0]=-1;
while(p--){
    scanf("%d",&pv);
    for(k=q-pv;k>=0;k--)
        if(dp[k])
            for(i=pv;i+k<=q;i+=pv)
                if(!dp[i+k] || num[k]+1<num[i+k] ||
				num[k]+1<=num[i+k] && use[k]<use[i+k-dp[i+k]]){
                    dp[i+k]=i;
                    use[i+k]=pv;
                    num[i+k]=num[k]+1;
                }
}
for(p=0;dp[q]>0;q-=dp[q]){
    if(!pu[use[q]])
        px[p++]=use[q];
    pu[use[q]]=1;
}
printf("%d",p);
qsort(px,p,sizeof(px[0]),numcmp);
while(p--)printf(" %d",px[p]);
puts("");
}
