#include<stdio.h>
struct RT{
    int x1,y1,x2,y2,r;
    RT operator&(RT& a){
        return(RT){x1>?a.x1,y1>?a.y1,x2<?a.x2,y2<?a.y2,r+a.r};
    }
    int S(){
        return (x2-x1)*(y2-y1);
    }
}now,tmp,rt[10000];
long long b[63];
//----------------------------------------------------------------
main(){
int i,j,n,m,x1,x2,y1,y2,sum;
for(i=b[0]=1;i<63;i++)b[i]=b[i-1]<<1;
//----------------------------------------------------------------
while(scanf("%d",&m) && m){
    n=1;
    rt[0]=(RT){0,0,10000,10000,0};
    //------------------------------------------------------------
    while(m--){
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        tmp=(RT){x1,y1,x2,y2,1};
        j=n;
        for(i=0;i<j;i++){
            now=rt[i]&tmp;
            rt[n++]=now;
        }
    }
    //------------------------------------------------------------
    sum=0;
    while(n--){
        for(i=rt[n].r,j=1;i>=0;i--){
            sum+=b[i]*rt[i].S()*j;
            j*=-i;
            j/=(rt[n].r-i+1);
        }
    }
    printf("%d\n",sum);
}
}
