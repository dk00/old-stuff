/*
ID: s0000151
PROG: cowcycle
LANG: C++
*/
#include<stdio.h>
int s,t,c,f,r,f1,f2,r1,r2,fgear[5],rgear[10],fset[5],rset[10];
double min=10e5,sum,mean,vari,ratio[50];
void calculate(){
    if(fgear[f-1]*rgear[r-1]<3*fgear[0]*rgear[0]) return;
    for(c=0,s=f-1;s>=0;s--)
        for(t=0;t<r;t++)
            ratio[c++]=double(fgear[s])/rgear[t];
    for(s=1;s<c;s++) {
        for(t=s;t>0 && ratio[t-1]<ratio[t];t--){
            mean=ratio[t-1]; ratio[t-1]=ratio[t]; ratio[t]=mean;
        }
    }
    for(c--,s=0;s<c;s++)ratio[s]-=ratio[s+1];
    for(mean=s=0;s<c;s++)mean+=ratio[s];
    for(mean/=c,vari=s=0;s<c;s++)vari+=ratio[s]*ratio[s];
    vari=vari/c-mean*mean;
    if(vari<min){
        min=vari-1e-13;
        for(s=0;s<f;s++)fset[s]=fgear[s];
        for(s=0;s<r;s++)rset[s]=rgear[s];
    }
}
void rcomp(int d,int i){
    if(d>=r){
        calculate();
        return;
    }
    for(;i<=r2;i++){
        rgear[d]=i;
        rcomp(d+1,i+1);
    }
}
void fcomp(int d,int i){
    if(d>=f){
        rcomp(0,r1);
        return;
    }
    for(;i<=f2;i++){
        fgear[d]=i;
        fcomp(d+1,i+1);
    }
}
main(){
freopen("cowcycle.in","r",stdin);
freopen("cowcycle.out","w",stdout);
scanf("%d %d %d %d %d %d",&f,&r,&f1,&f2,&r1,&r2);
fcomp(0,f1);
printf("%d",fset[0]);
for(s=1;s<f;s++)printf(" %d",fset[s]);
printf("\n%d",rset[0]);
for(s=1;s<r;s++)printf(" %d",rset[s]);
puts("");
}
