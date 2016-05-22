#include<math.h>
#include<stdio.h>
const double fix=100000.0;
double area(double x1,double y1_,double x2,double y2,double x3,double y3){
    return fabs(x1*y2+x2*y3+x3*y1_-x1*y3-x2*y1_-x3*y2);
}
double s,x1,x2,x3,y1_,y2,y3,sx,sy,ex,ey;
int inline intri(int x,int y){
    if(s<area(x,y,x2,y2,x3,y3)+area(x1,y1_,x,y,x3,y3)+
    area(x1,y1_,x2,y2,x,y))
        return 0;
    return 1;
}
main(){
int i,j,num;
while(scanf("%lf %lf %lf %lf %lf %lf",&x1,&y1_,&x2,&y2,&x3,&y3)){
    if(x1+x2+x3+y1_+y2+y3<=0)return 0;
    sx=floor(x1<?x2<?x3),ex=ceil(x1>?x2>?x3);
    sy=floor(y1_<?y2<?y3),ey=ceil(y1_>?y2>?y3);
    x1*=fix,x2*=fix,x3*=fix,y1_*=fix,y2*=fix,y3*=fix;
    s=area(x1,y1_,x2,y2,x3,y3);
    for(num=0,i=1;i<100;i++){
        if(i<sx || ex<i)continue;
        for(j=1;j<100;j++){
            if(j<sy || ey<j)continue;
            if(intri(i*fix,j*fix))num++;
        }
    }
    printf("%4d\n",num);
}
}

