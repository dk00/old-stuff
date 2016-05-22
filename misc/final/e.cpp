//e 

#include <stdio.h>
#define MAXNUM 15

const double eps=1e-9;
int n;

inline double Abs(double x)
{
  return (x>=0?x:0-x);
}

inline double Zero(double x)
{
  return Abs(x)<eps;
}

class Polynomial {
  public:
    int deg;
    double c[MAXNUM];
/*    void Print(void) {
      int i;
      for(i=deg;i>=0;i--) {
        printf("%.2lf ",c[i]);
      }
      printf("\n");
    }*/
    Polynomial() {
      int i;
      deg=n;
      for(i=0;i<=deg;i++) {
        c[i]=0.0;
      }
    }
    Polynomial(double a,int p) {
      int i;
      deg=n;
      for(i=0;i<=n;i++)
        c[i]=0.0;
      c[p]=a;
    }
    bool IsZero(void) const {
      int i;
      for(i=0;i<=deg;i++)
        if(!Zero(c[i])) break;
      return i>deg;
    }
    bool IsConstant(void) const {
      int i;
      for(i=1;i<=deg;i++)
        if(!Zero(c[i])) break;
      return i>deg;
    }
    int Highest(void) const {
      int i;
      for(i=deg;i>=0;i--)
        if(!Zero(c[i])) break;
      return i;
    }
    Polynomial& operator-=(const Polynomial &b) {
      int i;
      for(i=0;i<=deg;i++)
        c[i]-=b.c[i];
      return *this;
    }
    const Polynomial operator-(const Polynomial &b) const {
      return (Polynomial)*this-=b;
    }
    Polynomial& operator*=(const Polynomial &b) {
      int i,j;
      Polynomial a=*this;
      for(i=0;i<=deg;i++) {
        c[i]=0.0;
        for(j=0;j<=i;j++)
          c[i]+=a.c[j]*b.c[i-j];
      }
      return *this;
    }
    const Polynomial operator*(const Polynomial &b) const {
      return (Polynomial)*this*=b;
    }
    Polynomial& operator%=(const Polynomial &b) {
      int i,p;
      Polynomial m,s;
      p=b.Highest();
      for(i=deg;i>=p;i--) {
        if(Zero(c[i])) continue;
        m=Polynomial(c[i]/b.c[p],i-p);
        s=b*m;
        *this-=s;
      }
      return *this;
    }
    const Polynomial operator%(const Polynomial &b) const {
      return (Polynomial)*this%=b;
    }
    const Polynomial Deriative(void) const {
      int i;
      Polynomial p;
      for(i=deg;i>0;i--)
        p.c[i-1]=i*c[i];
      return p;
    }
};

Polynomial p,d;

Polynomial GCD(Polynomial a,Polynomial b)
{
  Polynomial temp;
  while(!b.IsZero()) {
//    a.Print();b.Print();
//    puts("");
    temp=b;
    b=a%b;
    a=temp;
  }
//  a.Print();
  return a;
}

inline bool Solve(void)
{
  d=p.Deriative();
//  d.Print();
//(GCD(d,p)).Print();
  return (GCD(d,p)).IsConstant();
}

int main(void)
{
  int t,i;
  scanf("%d",&t);
  while(t--) {
    scanf("%d",&n);
    p.deg=n;
    for(i=n;i>=0;i--)
      scanf("%lf",&p.c[i]);
    if(Solve()) printf("Yes\n");
    else printf("No\n");
  }
  return 0;
}
