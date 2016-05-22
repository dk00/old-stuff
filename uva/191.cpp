#include<stdio.h>
#include<stdlib.h>
struct pt{
    int x,y;
    void get(){
        scanf("%d %d",&x,&y);
    }
}p1,p2,r1,r2,r3,r4;
int rate(pt o,pt a,pt b){
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
int dis(pt a,pt b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
int ins(pt q1,pt q2){
    //a1 isn't in a2b1b2
    if(rate(p1,p2,q1)*rate(p1,p2,q2)<0 && rate(q1,q2,p1)*rate(q1,q2,p2)<0)
        return 1;
    if(rate(p1,p2,q1)==0 && dis(p1,p2)>=dis(p1,q1) &&
    dis(p1,p2)>=dis(p2,q1))return 1;
    if(rate(p1,p2,q2)==0 && dis(p1,p2)>=dis(p1,q2) &&
    dis(p1,p2)>=dis(p2,q2))return 1;
    if(rate(q1,q2,p2)==0 && dis(q1,q2)>=dis(q1,p2) &&
    dis(q1,q2)>=dis(q2,p2))return 1;
    if(rate(q1,q2,p1)==0 && dis(q1,q2)>=dis(q1,p1) &&
    dis(q1,q2)>=dis(q2,p1))return 1;
    return 0;}
int inn(pt p){
    return(p.x>=r1.x && p.x<=r2.x && p.y>=r1.y && p.y<=r2.y);
}
main(){
int t;
scanf("%d",&t);
while(t--){
    p1.get();
    p2.get();
    r1.get();
    r2.get();
    if(r1.x>r2.x){
        r1.x+=r2.x;
        r2.x=r1.x-r2.x;
        r1.x-=r2.x;
    }
    if(r1.y>r2.y){
        r1.y+=r2.y;
        r2.y=r1.y-r2.y;
        r1.y-=r2.y;
    }
    r3.x=r1.x,r3.y=r2.y;
    r4.x=r2.x,r4.y=r1.y;
    puts((ins(r1,r3) || ins(r1,r4) || ins (r3,r2) || ins(r2,r4)
    || inn(p1) || inn(p2))?"T":"F");
}
}
