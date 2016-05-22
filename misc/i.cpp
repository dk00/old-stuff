#include<stdio.h>
#include<algorithm>
#include<math.h>
int i;
double cx,cy,a[500][3],r,s,anx,any;
struct data{
	double x,y;
	bool operator<(data f)const{return x<f.x;}
}e[500];
double dis(double x1,double y1,double x2,double y2){
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int main(){
	int n;
	while(scanf("%d",&n)&&n){
		scanf("%lf %lf",&cx,&cy);
		for(i=0;i<n;i++){
			scanf("%lf %lf %lf",&a[i][0],&a[i][1],&a[i][2]);
			r=asin((a[i][0]-cx)/dis(a[i][0],a[i][1],cx,cy));
			s=asin(a[i][2]/dis(a[i][0],a[i][1],cx,cy));
			e[i].y=cx+cy*tan(r+s);
			e[i].x=cx+cy*tan(r-s);
		}
		std::sort(e,e+n);
		anx=e[0].x;
		any=e[0].y;
		for(i=1;i<n;i++){
			if(e[i].x<=any){
				any=e[i].y>any?e[i].y:any;
			}
			else{
				printf("%.2lf %.2lf\n",anx,any);
				anx=e[i].x;
				any=e[i].y;
			}
		}
		printf("%.2lf %.2lf\n\n",anx,any);
	}
	return 0;
}
