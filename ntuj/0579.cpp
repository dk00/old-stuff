#include <stdio.h>
#include <math.h>
#define MAXNUM 55
#define INF 1374.0
#define EPS 1e-6

double ABS(double x) {return (x>=0?x:0-x);}
bool Equal(double a,double b) {return ABS(a-b)<EPS;}

class Coor {
  public:
    double x,y,z;
    bool operator==(const Coor &b) {
      return (Equal(x,b.x)&&Equal(y,b.y)&&Equal(z,b.z));
    }
    bool operator!=(const Coor &b) {
      return !(*this==b);
    }
    Coor& operator+=(const Coor &b) {
      x+=b.x;
      y+=b.y;
      z+=b.z;
      return *this;
    }
    const Coor operator+(const Coor &b) const {
      return (Coor)*this+=b;
    }
    Coor& operator-=(const Coor &b) {
      x-=b.x;
      y-=b.y;
      z-=b.z;
      return *this;
    }
    const Coor operator-(const Coor &b) const {
      return (Coor)*this-=b;
    }
    Coor& operator*=(const double b) {
      x*=b;
      y*=b;
      z*=b;
      return *this;
    }
    const Coor operator*(const double &b) const {
      return (Coor)*this*=b;
    }
    Coor& operator/=(const double b) {
      x/=b;
      y/=b;
      z/=b;
      return *this;
    }
    const Coor operator/(const double &b) const {
      return (Coor)*this/=b;
    }
    const double Len(void) const {
      return sqrt(x*x+y*y+z*z);
    }
    const Coor Unit(void) const {
      double l=Len();
      if(l<EPS) {printf("[zero vector error]\n");return *this} // this shouldnt be allowed
      return (Coor)*this/l;
    }
};

Coor Top={INF,INF,INF};

double Dist(Coor a,Coor b) {
  return sqrt(a.x*b.x+a.y*b.y+a.z*b.z);
}

class Line {
  public:
    Coor a,b;
    const double Len(void) const {
      return Dist(a,b);
    }
};

class Plane {
  public:
    Coor v;
    double c;
};

double Dot(Coor a,Coor b) {
  return a.x*b.x+a.y*b.y+a.z*b.z;
}

double Cross(Coor a,Coor b) {
  return a.x*b.y+a.y*b.z+a.z*b.x-(a.y*b.x+a.x*b.z+a.z*b.y);
}

bool Perp(Coor a,Coor b) {
  return ABS(Dot(a,b))<EPS;
}

double Part(Coor a,Coor b) { // a on b
  return Dot(a,b)/b.len();
}

bool IsOn(Coor p,Line L) {
  if(ABS(Dist(p,L.a)+Dist(p,L.b)-Dist(L.a,L.b))<EPS);
}

Coor Nearest(Coor p,Line L) {
  if()
}

Coor Intersection(Plane P,Line L1,Line L2,Line L3,Line L4,Line L) {
  if(Perp(L.a-L.b,P.v)) { // parallel 
    if(Equal(Dot(P.v,L.a),c))
    // disjoint
    // on plane
    return Top;
  } else {
    return (a.x)
  }
}

int n;
double d,sidelen;
Coor Cube[MAXNUM][MAXNUM][MAXNUM];
Coor Bstart,Bdir;

Coor Intersect()

void Solve(void)
{
  int i,j,k;
  sidelen=d/n;
  for(i=0;i<=n;i++)
    for(j=0;j<=n;j++)
      for(k=0;k<=n;k++)
	Cube[i][j][k].x=i*sidelen,
	Cube[i][j][k].y=j*sidelen,
	Cube[i][j][k].z=k*sidelen;
  for(i=0;i<n;i++) {
    a
  }
}

int main(void)
{
  int i;
  while(scanf("%d",&n)==1&&n) {
    scanf("%lf",&d);
    scanf("%lf %lf %lf",&Bstart.x,&Bstart.y,&Bstart.z);
    scanf("%lf %lf %lf",&Bdir.x,&Bdir.y,&Bdir.z);
    Solve();
  }
  return 0;
}
