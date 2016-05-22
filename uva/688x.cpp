#include<stdio.h>
struct RT{
    double x1,y1,x2,y2,p;
    double s(){return (x2-x1)*(y2-y1)*p;}
}rt[100000];
void ins(RT a,RT b,RT &s){
    s=(RT){(a.x1>?b.x1),(a.y1>?b.y1),(a.x2<?b.x2),(a.y2<?b.y2),-b.p};
}
main(){
int i,j,k,n,C=1;
double x,y,r,s;
while(scanf("%d",&n) && n){
    for(s=i=0;n--;i=k){
        scanf("%lf %lf %lf",&x,&y,&r);
        rt[i]=(RT){x-r,y-r,x+r,y+r,1};
        for(j=0,k=i+1;j<i;j++){
            if(rt[i].x1>rt[j].x2 || rt[i].y1>rt[j].y2 || rt[i].x2<rt[j].x1 ||
            rt[i].y2<rt[j].y1)continue;
            if(rt[i].x1>=rt[j].x1 && rt[i].y1>=rt[j].y1 &&
            rt[i].x2<=rt[j].x2 && rt[i].y2<=rt[j].y2){
                k=i;
                break;
            }
            ins(rt[i],rt[j],rt[k++]);
        }
    }
    while(k--)s+=rt[k].s();
    printf("%d %.2lf\n",C++,s);
}
}
