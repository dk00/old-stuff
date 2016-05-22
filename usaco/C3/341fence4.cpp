/*
ID: s0000151
PROG:
LANG: C++
*/
#include<stdio.h>
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
        a=p;p=q;
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
    if((d1>0 && d2<0)||(d1<0 && d2>0 && d3>0 && d4<0)||(d3<0 && d4>0))
        return 1;
    if(!d1 && s.in(a))return 1;
    if(!d2 && s.in(b))return 1;
    if(!d3 && in(s.a))return 1;
    if(!d4 && in(s.b))return 1;
    return 0;
}
int closed(int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(i==j || i==(j+1)%n || i==j-1)continue;
            if(ll[i].intersect(ll[j]))return 0;
        }
    }
    return 1;
}
main(){
freopen("fence4.in","r",stdin);
freopen("fence4.out","w",stdout);
int n,i,j,k,visible[200],vis=0;
scanf("%d",&n);
s.get();
for(i=0;i<n;i++){
    p[i].get();
    ll[i].get(p[i],p[(i+1)%n]);
    visible[i]=0;
}
//if(!closed(n)){puts("NOFENCE");return 0;}
pos.a=s;
for(i=0;i<n;i++){
    pos.b=ll[i].a;
    for(j=k=0;j<n && !k;j++){
        if(i==j || i==j-1 || i==(j+1)%n)continue;
        if(pos.intersect(ll[j]))k++;
    }
    pos.b=ll[i].b;
    for(j=0;j<n && !k;j++){
        if(i==j || i==j-1 || i==(j+1)%n)continue;
        if(pos.intersect(ll[j]))k++;
    }
    if(!k)vis+=(visible[i]=1);
}
printf("%d\n",vis);
for(i=0;i<n;i++)
    if(visible[i])printf("%d %d %d %d",ll[i].a.x,ll[i].a.y,
    ll[i].b.x,ll[i].b.y);
}
