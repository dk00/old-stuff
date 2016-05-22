#include<stdio.h>
int abs(int n){
    if(n<0)return -n;
    return n;
}
class point{
public:
    int  x,y;
    point get(){
        scanf("%ld %ld",&x,&y);
        return *this;
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
    void show(){
        printf("%d %d\n",x,y);
    }
}temp[10005],ttttt;
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
    point p[10000];
    int n;
    void push(point p);
    void pop();
    int areax2();
    int in(point p);
    void show();
    polygon();
};
polygon::polygon(){
    n=0;
}
void polygon::push(point s){
    if(n<2){p[n++]=s;;return;}
    while(1){
        if(n<=2 || rate(p[n-2],p[n-1],s)<0){
            p[n++]=s;
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
void polygon::show(){
    printf("%d\n",n+1);
    int min,i;
    for(min=i=0;i<n;i++)
        if(p[i].y<p[min].y || (p[i].y==p[min].y &&p[i].x<p[min].x))
            min=i;
    for(i=min;i>=0;i--)p[i].show();
    for(i=n-1;i>=min;i--)p[i].show();
    
}
main(){
int k,n,j,min,p;
scanf("%d",&k);
printf("%d\n",k);
while(k--){
polygon s;
    scanf("%d",&n);
    for(min=s.n=j=0;j<n;j++){
        temp[j].get();
        if(temp[j]<temp[min])min=j;
    }
    ttttt=temp[min];temp[min]=temp[0];temp[0]=ttttt;
    for(p=1;p<n;p++)
        for(j=2;j<n;j++)
            if(rate(temp[0],temp[j],temp[j-1])<0){
                ttttt=temp[j];temp[j]=temp[j-1];temp[j-1]=ttttt;
            }
    for(j=0;j<n-1;j++)s.push(temp[j]);
    s.show();
    scanf("%d",&n);
    if(k)
        printf("%d\n",n);
}
}
