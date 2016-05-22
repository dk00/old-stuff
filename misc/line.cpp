int abs(int n){
    return n>=0?n:-n;
}
class point{
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
    point operator*(point s){
        return x*s.y-y*s.x;
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
    void get(){
        scanf("%d %d",&x,&y);
    }
};
class line{
    point a,b;
    void get(){
        a.get();
        b.get();
    }
    int in(point s);
    int intersect(line s);
};
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
       if((a-p)*(b-p)==0 || (a-p)*(c-p)==0 || (b-p)*(c-p)return 0;
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
        if(n<=2 || (p[n-1]-p[n-2])*(s-p[n-2]))<0){
            p[n++]=s;p[n]=p[0];
            return;
        }
        n--;
    }
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
