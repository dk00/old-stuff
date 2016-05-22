/*
ID: s0000151
PROG: fence3
LANG: C++
*/
#include<stdio.h>
#include<math.h>
int f,x1[150],x2[150],_y1[150],y2[150],dx[]={1,-1,0,0},dy[]={0,0,1,-1};
double abs(double n){
	return n<0?-n:n;
}
double min(double a,double b){
	return a>b?b:a;
}
double dis(double x3,double y3,double x4,double y4){
	return sqrt((x3-x4)*(x3-x4)+(y3-y4)*(y3-y4));
}
double calc(double x,double y){
int i;
double sum=0.0;
	for(i=0;i<f;i++)
		if(_y1[i]==y2[i]){
			if(x>=x1[i] && x<=x2[i])
				sum+=fabs(y-_y1[i]);
			else
				sum+=min(dis(x,y,x1[i],_y1[i]),dis(x,y,x2[i],y2[i]));
		}
		else if(x1[i]==x2[i]){
			if(y>=_y1[i] && y<=y2[i])
				sum+=fabs(x-x1[i]);
			else
				sum+=min(dis(x,y,x1[i],_y1[i]),dis(x,y,x2[i],y2[i]));
		}
	return sum;
}
void go(int d,double dv,double x,double y){
	if(d>=100){
		printf("%.1lf %.1lf %.1lf\n",x,y,calc(x,y));
		return;
	}
	double sx,sy,nx,ny,min=10e15,the;
	for(int i=0;i<4;i++){
		nx=x+dv*dx[i];
		ny=y+dv*dy[i];
		the=calc(nx,ny);
		if(the<min){
			min=the;
			sx=nx;sy=ny;
		}
	}
	go(d+1,dv*0.9,sx,sy);

}
main(){
freopen("fence3.in","r",stdin);
freopen("fence3.out","w",stdout);
int i;
scanf("%d",&f);
for(i=0;i<f;i++){
	scanf("%d %d %d %d",&x1[i],&_y1[i],&x2[i],&y2[i]);
	if(x1[i]>x2[i]){
		x1[i]+=x2[i];
		x2[i]=x1[i]-x2[i];
		x1[i]=x1[i]-x2[i];
	}
	if(_y1[i]>y2[i]){
		_y1[i]+=y2[i];
		y2[i]=_y1[i]-y2[i];
		_y1[i]=_y1[i]-y2[i];
	}
}
go(0,50,50,50);
}

		/*sum+=(x1[i]==x2[i]?
			y>=_y1[i] && y<=y2[i]?
				abs(x-x1[i])
				:min(dis(x,y,x1[i],_y1[i]),dis(x,y,x2[i],y2[i]))
			:x>=x1[i] && x<=x2[i]?
	    		abs(x-x1[i])
	    		:min(dis(x,y,x1[i],_y1[i]),dis(x,y,x2[i],y2[i])));*/
