#include<stdio.h>
struct pt{
    int x,y,id;
    int get(){
        scanf("%d %d",&x,&y);
        return x+y;
    }
}cv[1000],p[1000],C,tmp;
int dm(pt o,pt a,pt b){
    if(o.x==a.x && o.x==b.x)return a.y-b.y;
    if(o.y==a.y && o.y==b.y)return a.x-b.x;
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int lm(pt o,pt a,pt b){
    return!((a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x));
}
int onmess(pt A,pt B){
    int a,b,c;
    a=(B.x-C.x)*(B.x-C.x)+(B.y-C.y)*(B.y-C.y);
    b=(A.x-C.x)*(A.x-C.x)+(A.y-C.y)*(A.y-C.y);
    c=(A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
    if(a+c>=b && b+c>=a)return 1;
    return 0;
}
main(){
char s[1000];
int i,j,n,m,min,max;
while(scanf("%s",s) && *s-'#'){
    C.get();
    for(n=0;p[n].get();n++)p[n].id=n+1;
    min=0;
    for(i=1;i<n;i++)
        if(p[i].x<p[min].x || (p[i].x==p[min].x && p[i].y<p[min].y))
            min=i;
    tmp=p[min];p[min]=p[0];p[0]=tmp;
    for(i=1;i<n;i++)
        for(j=2;j<n;j++)
            if(dm(*p,p[j-1],p[j])<0){
                tmp=p[j-1];p[j-1]=p[j];p[j]=tmp;
            }
    cv[0]=p[0];
    cv[1]=p[1];
    for(i=j=2;i<n;i++){
        while(j>=2 && dm(cv[j-2],cv[j-1],p[i])<=0)j--;
        cv[j++]=p[i];
    }
    min=99999999;
    cv[m=j]=cv[0];
    for(i=0;i<m;i++){
        if(!onmess(cv[i],cv[i+1]))continue;
        for(max=j=0;j<n;j++)
            if(lm(cv[i],cv[i+1],p[j]))max>?=p[j].id;
        min<?=max;
    }
    printf("%-19s %2d\n",s,min);
}
}
