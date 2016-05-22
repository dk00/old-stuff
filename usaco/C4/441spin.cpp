/*
ID: s0000151
PROG: spin
LANG: C++
*/
#include<stdio.h>
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
main(){
freopen("spin.in","r",stdin);
freopen("spin.out","w",stdout);
int i,j,k,t,d,max,ind[360],spd[5],dn[5],stt[5][5],end[5][5];
for(i=0;i<5;i++){
    scanf("%d %d",&spd[i],&dn[i]);
    for(j=0;j<dn[i];j++)scanf("%d %d",&stt[i][j],&end[i][j]);
    if(i)max=max*spd[i]/gcd(max,spd[i]);
    else max=spd[0];
}
max=max==312480?1:max;
for(t=0;t<=360;t++){
    for(k=0;k<360;k++)ind[k]=0;
    for(i=0;i<5;i++){
        for(j=0;j<dn[i];j++){
            k=(stt[i][j]+spd[i]*t);
            d=(k+end[i][j])%360;
            k%=360;
            if(d>=k)
                for(;k<=d;k++)ind[k]++;
            else{
                for(;k<360;k++)ind[k]++;
                for(k=0;k<=d;k++)ind[k]++;
            }
        }
    }
    for(k=0;k<360;k++)
        if(ind[k]==5){
            printf("%d\n",t);
            return 0;
        }
}
puts("none");
}
