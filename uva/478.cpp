#include<stdio.h>
/*
    x1 x2 x3 x1
      x  x  x
    y1 y2 y3 y1
------------------
1/2|x1y2+x2y3+x3y1-x2y1-x3y2-x1y3|
*/
double abs(double n){
    if(n<0.0)return -n;
    return n;
}
class point{
public:
    double x,y;
    int get(){
        scanf("%lf %lf",&x,&y);
        if(x==9999.9 && y==9999.9)return 0;
        return 1;
    }
    int operator<(point p){
        if(x<p.x && y>p.y)return 1;
        return 0;
    }
    double distance(point p){
        return (x-p.x)*(x-p.x)+(y-p.y)*(y-p.y);
    }
    int line(point a,point b){
        return
        abs(abs((a.x-x)*(b.y-y))-abs((a.y-y)*(b.x-x)))<0.000001;
    }
};
double triarea(point a,point b,point c){
    return abs(a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y)/2;
}
class rectangle{
public:
    point lt,rd;
    void get(char *s){
        sscanf(s,"%lf %lf %lf %lf",&lt.x,&lt.y,&rd.x,&rd.y);
    }
    int in(point p){
        return(lt<p && p<rd);
    }
};
class circle{
public:
    point c;
    double r;
    void get(char *s){
        sscanf(s,"%lf %lf %lf",&c.x,&c.y,&r);
    }
    int in(point p){
        return(c.distance(p)<r*r);
    }
};
class triangle{
public:
    point a,b,c;
    void get(char *s){
        sscanf(s,"%lf %lf %lf %lf %lf %lf",
        &a.x,&a.y,&b.x,&b.y,&c.x,&c.y);
    }
    int in(point p){
        if(p.line(a,b) || p.line(a,c) || p.line(b,c))return 0;
        if(triarea(a,b,p)+triarea(a,p,c)+
        triarea(p,b,c)-triarea(a,b,c)>0.000001)return 0;
        return 1;
    }
};
main(){
rectangle rectangle[8];
circle circle[8];
triangle triangle[8];
point p;
char s[1000],sort[11];
int r=0,c=0,t=0,n=0,i,in,pn,figure[11];
while(gets(s) && s[0]!='*'){
    if(s[0]=='r'){
        figure[n]=r;
        rectangle[r++].get(&s[1]);
    }
    else if(s[0]=='c'){
        figure[n]=c;
        circle[c++].get(&s[1]);
    }
    else if(s[0]=='t'){
        figure[n]=t;
        triangle[t++].get(&s[1]);
    }
    else break;
    sort[n++]=s[0];
}
for(pn=1;p.get();pn++){
    for(in=i=0;i<n;i++){
        if(sort[i]=='r'){
            if(rectangle[figure[i]].in(p)){
                in++;
                printf("Point %d is contained in figure %d\n",pn,i+1);
            }
        }
        else if(sort[i]=='c'){
            if(circle[figure[i]].in(p)){
                in++;
                printf("Point %d is contained in figure %d\n",pn,i+1);
            }
        }
        else if(sort[i]=='t'){
            if(triangle[figure[i]].in(p)){
                in++;
                printf("Point %d is contained in figure %d\n",pn,i+1);
            }
        }
    }
    if(!in)printf("Point %d is not contained in any figure\n",pn);
}
}
