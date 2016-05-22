#include<stdio.h>
double abs(double n){
    return n<0?-n:n;
}
struct pt{
    double x,y;
    void get(){
        scanf("%lf %lf",&x,&y);
    }
    int operator==(pt s){
        return(abs(x-s.x)<1e-6 && abs(y-s.y)<1e-6);
    }
}p1[100],p2[100],tmp[1000],cov[1000],_;
int cn;
double dis(pt a,pt b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
double rate(pt o,pt a,pt b){
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
int atline(pt a,pt b,pt p){
    if(abs(rate(a,b,p))<1e-6&&dis(a,b)>=dis(a,p)&&dis(a,b)>=dis(b,p))
        return 1;
    return 0;
}
double area(pt *v,int n){
int i;
double s=0.0;
    for(i=0;i<n;i++)
        s+=v[i].x*v[i+1].y-v[i].y*v[i+1].x;
    return abs(s);
}
double area(pt a,pt b,pt c){
    if(a==b || a==c || b==c)return 0;
    return abs(a.x*b.y+b.x*c.y+c.x*a.y-a.x*c.y-b.x*a.y-c.x*b.y);
}
void insert(pt p1,pt p2,pt q1,pt q2){
pt p;
double a1=p2.y-p1.y,b1=p1.x-p2.x,c1=p1.x*a1+p1.y*b1,
       a2=q2.y-q1.y,b2=q1.x-q2.x,c2=q1.x*a2+q1.y*b2;
    if(a1*b2==a2*b1)return;
    p.x=(c1*b2-c2*b1)/(a1*b2-a2*b1);
    p.y=(a1*c2-a2*c1)/(a1*b2-a2*b1);
    if(atline(p1,p2,p) && atline(q1,q2,p))
        tmp[cn++]=p;
}
void inpoly(pt *v,int n,double parea,pt p){
int i;
    for(i=0;i<n;i++)
        parea-=area(p,v[i],v[i+1]);
    if(parea>=0.0)tmp[cn++]=p;
}
main(){
int i,j,n1,n2,min;
double a1,a2,ans;
while(scanf("%d",&n1) && n1){
    for(cn=i=0;i<n1;i++)p1[i].get();
    p1[n1]=p1[0];
    scanf("%d",&n2);
    for(i=0;i<n2;i++)p2[i].get();
    p2[n2]=p2[0];
    for(i=1;i<=n1;i++)
        for(j=1;j<=n2;j++)
            insert(p1[i-1],p1[i],p2[j-1],p2[j]);
    a1=area(p1,n1);
    a2=area(p2,n2);
    ans=a1+a2;
    for(i=0;i<n1;i++)
        inpoly(p2,n2,a2,p1[i]);
    for(i=0;i<n2;i++)
        inpoly(p1,n1,a1,p2[i]);
    for(min=i=0;i<cn;i++)
        if(tmp[i].x<tmp[min].x ||
        (tmp[i].x==tmp[min].x && tmp[i].y<tmp[min].y))min=i;
    _=tmp[0],tmp[0]=tmp[min],tmp[min]=_;
    for(j=0;j<cn;j++)
        for(i=j+1;i<cn;i++)
            if(tmp[i]==tmp[j]){
                _=tmp[cn-1],tmp[cn-1]=tmp[i],tmp[i]=_;
                cn--;
            }
    for(i=1;i<cn;i++)
        for(j=2;j<cn;j++)
            if(rate(tmp[0],tmp[j],tmp[j-1])<0 ||
            (rate==0 && dis(tmp[0],tmp[j-1])>dis(tmp[0],tmp[j]))){
                _=tmp[j],tmp[j]=tmp[j-1],tmp[j-1]=_;
            }
    cov[0]=tmp[--cn];
    for(i=1;cn--;i++){
        while(cn>=0 && cov[i-1]==tmp[cn])cn--;
        if(cn<0)break;
        cov[i]=tmp[cn];
    }
    cov[i]=cov[0];
    ans-=2*area(cov,i);
    printf("%8.2lf",ans/2);
}
puts("");
}
