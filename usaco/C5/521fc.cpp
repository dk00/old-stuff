/*
ID: s0000151
PROG: fc
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
double abs(double n){
    if(n<0.0)return -n;
    return n;
}
class point{
public:
    double x,y;
    void get(){
        scanf("%lf %lf",&x,&y);
    }
    int operator<(point s){
        if(x<s.x || (x==s.x && y<s.y))
        	return 1;
		return 0;
    }
    void operator=(point s){
        x=s.x;
        y=s.y;
    }
}temp[10000],temp101;
double rate(point o,point a,point b){
    double x1=a.x-o.x,x2=b.x-o.x,y1=a.y-o.y,y2=b.y-o.y;
    return x1*y2-x2*y1;
}
int pcmp(const void *a,const void *b){
    if(rate(temp[0],*(point *)a,*(point *)b)<0)return -1;
    return 1;
}
double dist(point a,point b){
	return sqrt(abs(a.x-b.x)*abs(a.x-b.x)+abs(a.y-b.y)*abs(a.y-b.y));
}
class polygon{
public:
    point p[10000];
    int n;
    void push(point p);
    void pop();
}fc;
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
main(){
freopen("fc.in","r",stdin);
freopen("fc.out","w",stdout);
int i,j,n,min;
double len=0.0;
scanf("%d",&n);
for(min=fc.n=j=0;j<n;j++){
    temp[j].get();
    if(temp[j]<temp[min])min=j;
}
temp101=temp[min];temp[min]=temp[0];temp[0]=temp101;
qsort(&temp[1],n-1,sizeof(temp[0]),pcmp);
for(j=0;j<n;j++)fc.push(temp[j]);
for(i=0;i<fc.n;i++)len+=dist(fc.p[i],fc.p[i+1]);
printf("%.2lf\n",len);
}
