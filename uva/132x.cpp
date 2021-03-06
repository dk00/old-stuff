#include<stdio.h>
#include<stdlib.h>
#include<string.h>
class point{
public:
   int x,y,id;
   int get(){
       scanf("%d %d",&x,&y);
       return x+y;
   }
   int operator<(point s){
       return x<s.x || (x==s.x && y<s.y);
   }
   void operator=(point s){
       x=s.x;
       y=s.y;
       id=s.id;
   }
}tmp,m,p[10000];
int rate(point o,point a,point b){
   int x1=a.x-o.x,x2=b.x-o.x,y1=a.y-o.y,y2=b.y-o.y;
   return x1*y2-x2*y1;
}
class polygon{
public:
   point p[10000];
   int n;
   void push(point p);
   void pop();
};
void polygon::push(point s){
   if(n<2){p[n++]=s;p[n]=p[0];return;}
   while(1){
       if(rate(p[n-2],p[n-1],s)<0 || n<2){
           p[n++]=s;p[n]=p[0];
           return;
       }
       pop();
   }
}
void polygon::pop(){
   n--;
}
int pointcmp(const void *a,const void *b){
   int r=rate(p[0],*(point *)a,*(point *)b);
   return r?r:*(point *)a<*(point *)b;
}
int massin(point a,point b){
   int
   dm=(a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y),
   da=(m.x-b.x)*(m.x-b.x)+(m.y-b.y)*(m.y-b.y),
   db=(a.x-m.x)*(a.x-m.x)+(a.y-m.y)*(a.y-m.y);
   if(da>dm+db)return 0;
   if(db>dm+da)return 0;
   return 1;
}
main(){
int i,n,min;
char name[100];
while(scanf("%s",name) && strcmp(name,"#")){
   polygon obj;
   obj.n=0;
   m.get();
   for(min=n=0;p[n].get();n++){
       p[n].id=n+1;
       if(p[n]<p[min])min=n;
   }
   tmp=p[min];
   p[min]=p[0];
   p[0]=tmp;
   qsort(&p[1],n-1,sizeof(p[0]),pointcmp);
   for(i=0;i<n;i++)obj.push(p[i]);
   min=n+1;
   for(i=0;i<obj.n;i++){
       if(massin(obj.p[i],obj.p[i+1]))
           min<?=((obj.p[i].id)>?(obj.p[i+1].id));
   }
   printf("%-19s %d\n",name,min);
}
}
