#include<math.h>
#include<stdio.h>
#include<stdlib.h>
struct point{
    int x,y,id;
}px[10000],py[10000],tmp[10000];
int n;
int xcmp(const void *a,const void *b){
    return ((point *)a)->x-((point *)b)->x;
}
int ycmp(const void *a,const void *b){
    return ((point *)a)->y-((point *)b)->y;
}
double dis(point a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
double find_bf(int stt,int end){
    int i,j;
    double min=100000000.0;
    for(i=0;i<end;i++)
        for(j=i+1;j<=end;j++)
            min<?=dis(px[i],px[j]);
    return min;
}
double find(int stt,int end){
    if(end-stt<=10000)return find_bf(stt,end);
    int mid=(stt+end)/2,p,p1,p2;
    double min=100000000.0;
    for(p=p1=stt,p2=mid+1;p<=end;p++){
        if(py[p].id==px[mid].id)continue;
        if(p1>=mid)tmp[p2++]=py[p];
        else if(p2>=end)tmp[p1++]=py[p];
        else if(py[p].x<=px[mid].x)tmp[p1++]=py[p];
        else tmp[p2++]=py[p];
    }
    for(p=stt;p<=end;p++)py[p]=tmp[p];
    py[mid]=px[mid];
    min<?=find(stt,mid-1);
    min<?=find(mid+1,end);
    for(p=stt,p1=stt,p2=mid+1;p<=end;p++){
        if(p==mid)tmp[p]=py[p];
        else if(p1>=mid)tmp[p]=py[p2++];
        else if(p2>=end)tmp[p]=py[p1++];
        else if(py[p1].y<=py[p2].y)tmp[p]=py[p1++];
        else tmp[p]=py[p2++];
    }
    for(p=stt;p<=end;p++)py[p]=tmp[p];
    for(p=p1=stt;p1<=end;p1++)
        if(py[p1].x-px[mid].x<=min || py[p1].x-px[mid].x>=-min)
            tmp[p++]=py[p1];
    for(p1=stt;p1<p;p1++)
        for(p2=p1+1;p2<p;p2++){
            if(py[p2].y-py[p1].y>=min)break;
            min<?=dis(py[p1],py[p2]);
        }
    return min;
}
main(){
int i;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++){
        scanf("%d %d",&px[i].x,&px[i].y);
        px[i].id=i;
        py[i]=px[i];
    }
    qsort(px,n,sizeof(px[0]),xcmp);
    qsort(py,n,sizeof(py[0]),ycmp);
    double min=find(0,n-1);
    if(min<10000.0)
        printf("%.4lf\n",min);
    else puts("INFINITY");
}
}
