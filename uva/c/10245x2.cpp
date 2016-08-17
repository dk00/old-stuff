#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#define dis(a,b) (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y)
struct point{
    double x,y;
    void get(){
        scanf("%lf %lf",&x,&y);
    }
}p[10000];
int pointcmp(const void *a,const void *b){
    return(((point *)a)->x-((point *)b)->x>=0);
}
double min;
main(){
int i,j,n;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        p[i].get();
    min=100000000.0;
    qsort(p,n,sizeof(p[0]),pointcmp);
    for(i=0;i<n-1;i++)
        min<?=dis(p[i],p[i+1]);
    for(i=0;i<n;i++)
        for(j=i+1;j<n && p[j].x-p[i].x<min;j++)
            min<?=dis(p[i],p[j]);
    if(min<=100000000.0)
        printf("%.4lf\n",sqrt(min));
    else
        puts("INFINITY");
}
}
