#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct point{
    int x,y;
}x[10000],y[10000],tmp[10000];
int xcmp(const void *a,const void *b){
    return((point *)a)->x-((point *)b)->x;
}
int ycmp(const void *a,const void *b){
    return((point *)a)->y-((point *)b)->y;
}
double dis(point a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double pairfind(int stt,int end){
    //bound
    if(end-stt==1)
        return dis(x[stt],x[end]);
    if(end-stt==2)
        return(dis(x[stt],x[stt+1])<?dis(x[stt],x[end])<?dis(x[stt+1],x[end]));
    //divide
    int mid=(stt+end)/2,p,p1,p2;
    for(p=p1=stt,p2=mid+1;p<=end;p++){
        if(p2>end || y[p].x<=x[mid].x)
            tmp[p1++]=y[p];
        else
            tmp[p2++]=y[p];
    }
    for(p=end;p>=stt;p--)
        y[p]=tmp[p];
    //conquer
    double min=(pairfind(stt,mid)<?pairfind(mid+1,end)),m2;
    //combine
    for(p=p1=stt;p1<=end;p1++)
        if(y[p1].x-x[mid].x<min && y[p1].x-x[mid].x>-min)
            tmp[p++]=y[p1];
    m2=min;
    for(p1=stt;p1<p;p1++)
        for(p2=p1+1;tmp[p2].y-tmp[p1].y<min;p2++)
            m2<?=dis(tmp[p1],tmp[p2]);
    return(m2<?min);
}
main(){
int i,n;
double min;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++){
        scanf("%d %d",&x[i].x,&x[i].y);
        y[i]=x[i];
    }
    if(n<=1){
        puts("INFINITY");
        continue;
    }
    qsort(x,n,sizeof(x[0]),xcmp);
    qsort(y,n,sizeof(y[0]),ycmp);
    min=pairfind(0,n-1);
    if(min<10000.0)
        printf("%.4lf\n",min);
    else
        puts("INFINITY");
}
}
