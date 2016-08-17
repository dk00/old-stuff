#include<stdio.h>
struct RT{
    double x1,y1,x2,y2;
}tmp[100],rt[100];
double sum;
int check(int p){
    for(int j=p;j--;)
        if(tmp[p].x1>=tmp[j].x1 && tmp[p].y1>=tmp[j].y1 &&
        tmp[p].y2<=tmp[j].y2 && tmp[p].x2<=tmp[p].x2)return 0;
    return 1;
}
int calc(int i,double x1,double y1,double x2,double y2,int r){
    sum+=(x2-x1)*(y2-y1)*r;
    while(i--){
        if(x1>rt[i].x2 || y1>rt[i].y2 || x2<rt[i].x1 || y2<rt[i].y1)
            continue;
        calc(i,x1>?rt[i].x1,y1>?rt[i].y1,x2<?rt[i].x2,y2<?rt[i].y2,-r);
    }
}
main(){
int i,j,n,x,y,r,C=1;
while(scanf("%d",&n) && n){
    for(sum=i=j=0;i<n;i++){
        scanf("%lf %lf %lf",&x,&y,&r);
        tmp[i++]=(RT){x-r,y-r,x+r,y+r};
    }
    while(n--)
        if(check(n))rt[j++]=tmp[n];
    while(j--)
        calc(j,rt[j].x1,rt[j].y1,rt[j].x2,rt[j].y2,1);
    printf("%d %.2lf\n",C++,sum);
}
}
