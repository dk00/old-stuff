#include<math.h>
#include<stdio.h>
using namespace std;
const double pi=acos(-1);
double x,y,r,d,s,s1,s2;
int n,p,sum;
struct anr{
    double s1,s2;
}a[10000];
int check(int x1,int y1){
    d=sqrt((x1-x)*(x1-x)+(y1-y)*(y1-y));
    s=asin((y-y1)/d);
    if(y-y1>0 && x-x1<0)s+=pi/2;
    if(y-y1<0 && x-x1<0)s+=pi/2;
    s1-=r/d;
    for(p=0;p<n;p++){
        if(s1<a[p].s1 && s2>a[p].s2)continue;
        return 0;
    }
    a[n++]=(anr){s1,s2};
    return 1;
}
main(){
int i,j;
while(scanf("%lf %lf %lf",&r,&x,&y) && r+x+y>0.0){
    r/=2;
    n=sum=0;
    for(i=0;i<600;i++){
        for(j=-i;j<=i+1;j++){
            sum+=check(-i,j);
            sum+=check(j,-i);
            sum+=check(i+1,j);
            sum+=check(j,i+1);
        }
    }
    printf("%d\n",sum);
}
}
