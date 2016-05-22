/*
ID: s0000151
PROG: fence4
LANG: C++
*/
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int n;
double dis[200];
class point{
public:
    int x,y;
    point operator+(point s){
        point tmp;
        tmp.x=x+s.x;
        tmp.y=y+s.y;
        return tmp;
    }
    point operator-(point s){
        point tmp;
        tmp.x=x-s.x;
        tmp.y=y-s.y;
        return tmp;
    }
    int operator*(point s){
        return (x*s.y)-(y*s.x);
    }
    int operator<(point s){
        return x<s.x && y<s.y;
    }
    int operator<=(point s){
        return x<=s.x && y<=s.y;
    }
    int operator==(point s){
        return x==s.x && y==s.y;
    }
    void operator=(point s){
        x=s.x;y=s.y;
    }
    void get(){
        scanf("%d %d",&x,&y);
    }
    void set(int p,int q){
        x=p;y=q;
    }
}p[200],s,t;
class line{
public:
    point a,b;
    void get(point p,point q){
        a=p;b=q;
    }
    int in(point s);
    int intersect(line s);
    void operator=(line s){
        a=s.a;b=s.b;
    }
}ll[200],ins[200],pos;
int line::in(point s){
    return (a.x<?b.x)<=s.x && s.x<=(a.x>?b.x)
      &&   (a.y<?b.y)<=s.y && s.y<=(a.y>?b.y);
}
int line::intersect(line s){
    int d1=(s.a-a)*(s.b-a),
        d2=(s.a-b)*(s.b-b),
        d3=(a-s.a)*(b-s.a),
        d4=(a-s.b)*(b-s.b);
    if(d1*d2<0 && d3*d4<0)
        return 1;
    if(!d1 && s.in(a))return 1;
    if(!d2 && s.in(b))return 1;
    if(!d3 && in(s.a))return 1;
    if(!d4 && in(s.b))return 1;
    return 0;
}
point mid(point a,point b){
    t.x=(a.x+b.x)/2;
    t.y=(a.y+b.y)/2;
}
int closed(int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=i;j<n;j++){
            if(i==j || i==(j+1)%n || i==j-1)continue;
            if(ll[i].intersect(ll[j]))return 0;
        }
    }
    return 1;
}
main(){
freopen("fence4.in","r",stdin);
freopen("fence4.out","w",stdout);
int i,j,k,visible[200],vis=0;
scanf("%d",&n);     //input
s.get();
for(i=0;i<n;i++){
    p[i].get();
    visible[i]=0;
}
for(i=0;i<n;i++)ll[i].get(p[i],p[(i+1)%n]);
if(closed(n)==0){puts("NOFENCE");return 0;}     //if is nofence
pos=ll[n-1];ll[n-1]=ll[n-2];ll[n-2]=pos;
t=ll[n-2].a;ll[n-2].a=ll[n-2].b;ll[n-2].b=t;    //input
pos.a=s;
for(i=0;i<n;i++){

}
for(i=vis=0;i<n;i++)vis+=visible[i];
printf("%d\n",vis);
for(i=0;i<n;i++)
    if(visible[i])printf("%d %d %d %d\n",ll[i].a.x,ll[i].a.y,
    ll[i].b.x,ll[i].b.y);
}
