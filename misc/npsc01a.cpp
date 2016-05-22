#include<stdio.h>
struct RT{
    int x1,y1,x2,y2,r;
    RT operator+(RT& p){
        return(RT){x1>?p.x1,y1>?p.y1,x2<?p.x2,y2<?p.y2,r*p.r};
    }
    RT operator-(RT& p){
        return(RT){x1>?p.x1,y1>?p.y1,x2<?p.x2,y2<?p.y2,-r-p.r};
    }
    bool operator==(RT &s){
        return(x1==s.x1 && y1==s.y1 && x2==s.x2 && y2==s.y2);
    }
}now,rt[10000];
main(){
int i,j,k,n,m,sum,x1,x2,y1,y2;
while(scanf("%d",&m) && m){
    n=sum=0;
    rt[n++]={0,0,10000,10000,1};
    while(m--){
        scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
        rt[n]=(RT){x1,y1,x2,y2,2};
        j=n++;
        for(i=0;i<j;i++){
            rt[n++]=rt[i]+rt[j];
            rt[n++]=rt[i]-rt[j];
        }
    }
    while(n--)
        sum+=(rt[n].x2-rt[n].x1)*(rt[n].y2-rt[n].y1)*rt[i].r;
    printf("%d\n",sum);
}
}
