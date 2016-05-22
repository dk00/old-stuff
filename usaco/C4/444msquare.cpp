/*
ID: s0000151
PROG: msquare
LANG: C++
*/
#include<stdio.h>
#define C1 cor[0]
#define C2 cor[1]
#define C3 cor[2]
#define C4 cor[3]
#define C5 cor[4]
#define C6 cor[5]
#define C7 cor[6]
#define C8 cor[7]
int done[40320],last[40320],f[8],use[8]={1,1,1,1,1,1,1,1};
class square{
public:
    int cor[8];
    char a;
    void get(){
        scanf("%d %d %d %d %d %d %d %d",
        &C1,&C2,&C3,&C4,&C8,&C7,&C6,&C5)==8;
        C1--;C2--;C3--;C4--;C5--;C6--;C7--;C8--;
    }
    void A(square s){
        C1=s.C5;C2=s.C6;C3=s.C7;C4=s.C8;
        C5=s.C1;C6=s.C2;C7=s.C3;C8=s.C4;
        a='A';
    }
    void B(square s){
        C1=s.C4;C2=s.C1;C3=s.C2;C4=s.C3;
        C5=s.C8;C6=s.C5;C7=s.C6;C8=s.C7;
        a='B';
    }
    void C(square s){
        C1=s.C1;C2=s.C6;C3=s.C2;C4=s.C4;
        C5=s.C5;C6=s.C7;C7=s.C3;C8=s.C8;
        a='C';
    }
}q[40320],target;
int N(square sq,int d){
    if(d<0)return 0;
    int i,k;
    for(k=i=0;i!=sq.cor[d];i++)k+=use[i];
    k=f[d]*k;
    use[sq.cor[d]]=0;
    k+=N(sq,d-1);
    use[sq.cor[d]]=1;
    return k;
}
main(){
freopen("msquare.in","r",stdin);
freopen("msquare.out","w",stdout);
int i,j,tn;
char path[10000];
for(f[0]=i=1;i<8;i++)f[i]=f[i-1]*i;
target.get();
tn=N(target,7);
for(i=0;i<4;i++)q[0].cor[i]=i;
for(i=4;i<8;i++)q[0].cor[i]=11-i;
for(i=0,j=1;;i++){
    if(N(q[i],7)==tn)break;
    q[j].A(q[i]);
    if(!done[N(q[j],7)]){
        done[N(q[j],7)]=1;
        last[j++]=i;
    }
    q[j].B(q[i]);
    if(!done[N(q[j],7)]){
        done[N(q[j],7)]=1;
        last[j++]=i;
    }
    q[j].C(q[i]);
    if(!done[N(q[j],7)]){
        done[N(q[j],7)]=1;
        last[j++]=i;
    }
}
for(j=0;i;i=last[i])
    path[j++]=q[i].a;
printf("%d",j);
if(!j)puts("");
for(i=0;j--;i++){
    if(i%60==0)puts("");
    printf("%c",path[j]);
}
puts("");
}
