#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
struct pt{
    double x,y,z;
    pt& operator-=(pt a){
	x-=a.x;
	y-=a.y;
	z-=a.z;
	return *this;
    }
    pt& operator~(){
	swap(x,y);
	swap(y,z);
	return *this;
    }
    bool operator>(int d)const{
	return x>d && y>d && z>d;
    }
};
const int N=55;
int n,un,u[N][N][N];
double d,m,minz;
pt cross(pt& o,pt& d,double x0)
{
    pt tmp;
    tmp.x=x0;
    tmp.y=(x0-o.x)/d.x*d.y;
    tmp.z=(x0-o.x)/d.x*d.z;
}
bool in(double x,double y,double z,pt a)
{
    return(x<=a.x && a.x<=x+d && y<=a.y && a.y<=y+d && z<=a.z && a.z<=z+d);
}
void add(pt a)
{
    if(a>m)return;
    int i,j,k,x,y,z;
    x=floor(a.x/d);
    y=floor(a.y/d);
    z=floor(a.z/d);
    for(i=x-1;i<=x+1;i++)
	for(j=y-1;j<=y+1;j++)
	    for(k=z-1;k<=z+1;k++)
		if(in(i,j,k,a))u[i][j][k]=un;
    if(a.z<minz)minz=a.z;
}
main()
{
    int i,j,k,C=0;
    pt st,ed;
    while(scanf("%d %lf %lf%lf%lf %lf%lf%lf",
	&n,&m,&st.x,&st.y,&st.z,&ed.x,&ed.y,&ed.z)>0 && n){
	ed-=st;
	for(i=0,un++;i<n;i++){
	    pt tmp=cross(st,ed,d*i/n);
	    add(tmp);
	    st=~st;
	    ed=~ed;
	    tmp=cross(st,ed,d*i/n);
	    tmp=~(~tmp);
	    add(tmp);
	    st=~st;
	    ed=~ed;
	    tmp=cross(st,ed,d*i/n);
	    tmp=~tmp;
	    add(tmp);
	}
	double sum=0;
	int mink=floor(minz/d);
	for(i=0;i<n;i++)
	    for(j=0;j<n;j++)
		for(k=0;k<n;k++)
		    if(u[i][j][k]==un){
			if(k>mink)
			    sum+=d*d*mink;
			else
			    sum+=d*d*d;
		    }
	printf("Trial %d, Volume = %.2lf\n",C++,sum);
    }
}
