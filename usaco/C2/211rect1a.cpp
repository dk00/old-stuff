/*
ID: s0000151
PROG: rect1
LANG: C++
*/
#include<stdio.h>
int rect,num[2500],llx[1000],lly[1000],urx[1000],ury[1000],cor[1000];
void put(int d,int x1,int y1,int x2,int y2){
    if(d<=rect){
        num[cor[rect]]+=(x2-x1+1)*(y2-y1+1);
        num[1]-=(x2-x1+1)*(y2-y1+1);
        return;
    }
    if(x1>urx[d] || y1>ury[d] || x2<llx[d] || y2<lly[d]){
        put(d-1,x1,y1,x2,y2);
        return;
    }
    if(x1<llx[d])put(d-1,x1,y1,llx[d]-1,y2);
    if(x2>urx[d])put(d-1,urx[d]+1,y1,x2,y2);
    if(y1<lly[d])put(d-1,llx[d]>?x1,y1,urx[d]<?x2,lly[d]-1);
    if(y2>ury[d])put(d-1,llx[d]>?x1,ury[d]+1,urx[d]<?x2,y2);
}
main(){
int i,n,w,h,max;
freopen("rect1.in","r",stdin);
freopen("rect1.out","w",stdout);
scanf("%d %d %d",&h,&w,&n);
for(max=i=0;i<n;i++){
    scanf("%d %d %d %d %d",&llx[i],&lly[i],&urx[i],&ury[i],&cor[i]);
    urx[i]--,ury[i]--;
    max>?=cor[i];
}
for(rect=n;rect--;)
    put(n-1,llx[rect],lly[rect],urx[rect],ury[rect]);
num[1]+=w*h;
for(i=1;i<=max;i++)
    if(num[i])
        printf("%d %d\n",i,num[i]);
}
