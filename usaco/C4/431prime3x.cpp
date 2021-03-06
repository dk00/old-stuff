/*
ID: s0000151
PROG: prime3
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define DEBUG 0
int p,z,s,lu,tmp,sum,notp[100000],prime[10000],primez[10000],primel[10000]
,d00,d01,d02,d03,d04,d10,d11,d12,d13,d14,d20,d21,d22,d23,d24,d30,d31,d32,
d33,d34,d40,d41,d42,d43,d44,*ptr[5][5]={{&d00,&d01,&d02,&d03,&d04},
{&d10,&d11,&d12,&d13,&d14},{&d20,&d21,&d22,&d23,&d24},
{&d30,&d31,&d32,&d33,&d34},{&d40,&d41,&d42,&d43,&d44}},aaa=0,
lim1,lim2,lim5;
char ans[500][26];
void six();
void five();
void four();
void three();
void two();
void one();
int cmp(const void *a,const void *b){
    return -strcmp((char *)a,(char *)b);
}
main(){
if(!DEBUG){freopen("prime3.in","r",stdin);
freopen("prime3.out","w",stdout);}
int i,j,k;
scanf("%d %d",&sum,&lu);
for(z=s=p=0,i=3;i<10000;i++,i++){
    if(notp[i])continue;
    for(j=i*3;j<100000;j+=i*2)notp[j]=1;
}
for(i=10001;i<100000;i++,i++){
    if(notp[i])continue;
    for(j=i;j<100000;j+=i*2)notp[j]=1;
    d00=i/10000;d01=(i/1000)%10;d02=(i/100)%10;d03=(i/10)%10;d04=i%10;
    j=d00+d01+d02+d03+d04;
    if(sum==j){
        prime[p++]=i;
        if(d00==lu)primel[s++]=i;
        if(d01 && d02 && d03){
            if(d00==lu)primez[z++]=i;
        }
        notp[i]=0;
    }
}
Solve This Problem;
if(!aaa)puts("NONE");
else{
    qsort(ans,aaa,sizeof(ans[0]),cmp);
    six();
}
if(DEBUG)scanf(" ");
}
void one(){
    d00=lu;
    int i,j,k;
    for(i=0;i<z;i++){
        tmp=primez[i];
        d01=(tmp/1000)%10;
        d02=(tmp/100)%10;
        d03=(tmp/10)%10;
        d04=tmp%10;
        for(j=0;j<z;j++){
            tmp=primez[j];
            d10=(tmp/1000)%10;
            d20=(tmp/100)%10;
            d30=(tmp/10)%10;
            d40=tmp%10;
            for(k=0;k<s;k++){
                tmp=primel[k];
                d11=(tmp/1000)%10;
                d22=(tmp/100)%10;
                d33=(tmp/10)%10;
                d44=tmp%10;
                if(d40+d04+d22<sum && d10+d11<sum && d01+d11<sum &&
                d02+d22<sum && d20+d22<sum && d30+d33<sum && d03+d33<sum
                && d04+d44<sum && d40+d44<sum)two();
            }
        }
    }
}
void two(){
    int i,lim=sum-d04-d40-d22;
    if(lim>18)return;
    for(i=0;i<10 && lim-i>=0;i++){
        if(lim-i>=10)continue;
        d13=i;d31=lim-i;
        if(!notp[d04+d13*10+d22*100+d31*1000+d40*10000] &&
        d10+d11+d13<sum && d30+d31+d33<sum && d01+d11+d31<sum &&
        d03+d13+d33<sum)three();
    }

}
void three(){
    register int i,j;
    lim1=sum-d10-d11-d13;
    lim2=sum-d01-d11-d31;
    if(lim1>18 || lim2>18)return;
    for(i=1;i<10 && lim1-i>=0;i++,i++){
        if(lim1-i>=10 || i==5)continue;
        d12=lim1-i;d14=i;
        if(notp[d10*10000+d11*1000+d12*100+d13*10+d14] ||
        d02+d12+d22>=sum || d04+d14+d44>=sum)continue;
        for(j=1;j<10 && lim2-j>=0;j++,j++){
            if(lim2-j>=10 || j==5)continue;
            d21=lim2-j;d41=j;
            if(!notp[d01*10000+d11*1000+d21*100+d31*10+d41] &&
            d20+d21+d22<sum && d40+d41+d44<sum)four();
        }
    }
}
void four(){
    if((sum-d40-d41-d44)%2 || (sum-d04-d14-d44)%2)return;
    lim5=sum-d40-d41-d44;
    for(d43=1;d43<10 && lim5-d43>0;d43++,d43++){
        if(lim5-d43>=10)continue;
        d42=lim5-d43;
        d23=sum-d03-d13-d33-d43;
        d32=sum-d02-d12-d22-d42;
        d24=sum-d20-d21-d22-d23;
        d34=sum-d30-d31-d32-d33;
        if(d24%2==0 || d34%2==0)continue;
        if(d23<0 || d32<0 || d24<1 || d34<1 || d23>9 || d32>9 || d24>9
        || d34>9)continue;
        if(!notp[d02*10000+d12*1000+d22*100+d32*10+d42] &&
           !notp[d03*10000+d13*1000+d23*100+d33*10+d43] &&
           !notp[d04*10000+d14*1000+d24*100+d34*10+d44] &&
           !notp[d20*10000+d21*1000+d22*100+d23*10+d24] &&
           !notp[d30*10000+d31*1000+d32*100+d33*10+d34] &&
           !notp[d40*10000+d41*1000+d42*100+d43*10+d44])
           five();
    }
}
int ii,jj;
void five(){
    for(ii=0;ii<5;ii++)
        for(jj=0;jj<5;jj++)ans[aaa][ii*5+jj]=*ptr[ii][jj]+'0';
    aaa++;
}
void six(){
    int i,j;
    while(aaa--){
        for(i=0;i<5;i++){
            for(j=0;j<5;j++)
            printf("%c",ans[aaa][i*5+j]);
            puts("");
        }
        if(aaa)puts("");
    }
}
