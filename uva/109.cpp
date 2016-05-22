#include<stdio.h>
int abs(int n){
    if(n<0)return -n;
    return n;
}
class point{
public:
    int  x,y;
    int get(){
        if(scanf("%ld %ld",&x,&y)==EOF)return 0;
        return 1;
    }
    int operator<(point s){
        return x<s.x || (x==s.x && y<s.y);
    }
    void operator=(point s){
        x=s.x;
        y=s.y;
    }
    int linein(point a,point b){
        return
        abs(abs((a.x-x)*(b.y-y))-abs((a.y-y)*(b.x-x)))<0.000001;
    }
}temp[100],SCUD;
int triarea(point a,point b,point c){
   return abs(a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y)/2;
}
class triangle{
public:
   point a,b,c;
   void get(point p,point q,point r){
        a=p;b=q;c=r;
    }
   int in(point p){
       if(p.linein(a,b) || p.linein(a,c) || p.linein(b,c))return 0;
       if(triarea(a,b,p)+triarea(a,p,c)+
       triarea(p,b,c)-triarea(a,b,c)>0.000001)return 0;
       return 1;
   }
}tri;
long rate(point o,point a,point b){
    int x1=a.x-o.x,x2=b.x-o.x,y1=a.y-o.y,y2=b.y-o.y;
    return x1*y2-x2*y1;
}
class polygon{
public:
    point p[100];
    int n;
    void push(point p);
    void pop();
    int areax2();
    int in(point p);
}k[20];
void polygon::push(point s){
    if(n<=2){p[n++]=s;p[n]=p[0];return;}
    while(1){
        if(rate(p[n-2],p[n-1],s)<0 || n<=2){
            p[n++]=s;p[n]=p[0];
            return;
        }
        pop();
    }
}
void polygon::pop(){
    n--;
}
int polygon::areax2(){
    int tpp=0;
    for(int i=1;i<=n;i++)tpp+=p[i].x*p[i-1].y-p[i-1].x*p[i].y;
    return abs(tpp);
}
int polygon::in(point s){
    for(int i=2;i<n;i++){
        tri.get(p[0],p[i-1],p[i]);
        if(tri.in(s))return 1;
    }
    return 0;
}
main(){
int i,j,p,min,n,area[20],sum,hit[20];
for(i=0;scanf("%d",&n) && n>=0;i++){
    for(min=k[i].n=j=0;j<n;j++){
        temp[j].get();
        if(temp[j]<temp[min])min=j;
    }
    temp[101]=temp[min];temp[min]=temp[0];temp[0]=temp[101];
    for(p=1;p<n;p++)
        for(j=2;j<n;j++)
            if(rate(temp[0],temp[j],temp[j-1])<0){
                temp[101]=temp[j];temp[j]=temp[j-1];temp[j-1]=temp[101];
            }
    for(j=0;j<n;j++)k[i].push(temp[j]);
    area[i]=k[i].areax2();
    hit[i]=0;
}n=i;
while(SCUD.get())for(i=0;i<n;i++)if(k[i].in(SCUD))hit[i]++;
for(sum=i=0;i<n;i++)if(hit[i])sum+=area[i];
printf("%d.%d0\n",sum/2,sum%2?5:0);
}
