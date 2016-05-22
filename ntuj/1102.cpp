#include<algorithm>
#include<cstdio>
#include<cmath>
using namespace std;
#define N 1005
double ans,eps=1e-6;
void check(double* A, double* B, double* V, double r1, double r2, double tb, double te){
  if(te-tb<eps)
    return;
  double a,b,c,d;
  double t1,t2;
  a=0;
  for(int k=0;k<3;++k)
    a+=V[k]*V[k];
  b=0;
  for(int k=0;k<3;++k)
    b+=2*(B[k]-A[k])*V[k];
  c=0;
  for(int k=0;k<3;++k)
    c+=(A[k]-B[k])*(A[k]-B[k]);
  c-=(r1+r2)*(r1+r2);

  d = b*b - 4*a*c;
  if(d < -eps) 
    return;
  if(a>eps || -a>eps){
    t1 = (-b - sqrt(d)) / (2*a);
    t2 = (-b + sqrt(d)) / (2*a);
    if(t1>eps && tb+t1<te+eps){
      if(ans==-1 || tb+t1 < ans)
        ans = tb+t1;
    }
    else if(t2>eps && tb+t2<te+eps){
      if(ans==-1 || tb+t2 < ans)
        ans = tb+t2;
    }  
  }
  else{
    if(b>eps || -b>eps)
      t1 = -c/b;
    else
      return;
    if(t1>eps && tb+t1<te+eps){
      if(ans==-1 || tb+t1 < ans)
        ans = tb+t1;
    }
  }
}
int main(void){
  long long s[N][3],g[N][3],r[N],vi[N],t[N];
  double u[N][3],v[3],te[N];
  int n;
  while(scanf("%d",&n)){
    if(n==-1)
      break;
    //input
    for(int i=0;i<n;++i){
      for(int j=0;j<3;++j)
        scanf("%lld",&s[i][j]);
      for(int j=0;j<3;++j)
        scanf("%lld",&g[i][j]);
      scanf("%lld%lld%lld",&r[i],&t[i],&vi[i]);

      //compute te
      double dis = 0;
      for(int j=0;j<3;++j)
        dis += (g[i][j]-s[i][j])*(g[i][j]-s[i][j]);
      dis = sqrt(dis);
      te[i] = t[i]+dis/vi[i] + eps;
      //compute v vector
      double mul=0;
      for(int j=0;j<3;++j)
        mul += (g[i][j] - s[i][j])*(g[i][j] - s[i][j]);
      mul = vi[i]/sqrt(mul);
      for(int j=0;j<3;++j)
        u[i][j] = mul*(g[i][j]-s[i][j]);
    }
    ans = -1;
    //check each pair
    for(int i=0;i<n;++i)
      for(int j=i+1;j<n;++j){
        double A[3], B[3],tb, tn;
        int x,y;
        if(t[i]<=t[j]) { x=i; y=j;}
        else {x=j; y=i;}
        //case 1  only x move
        tb = t[x]; tn = min(te[x],(double)t[y]);
        for(int k=0;k<3;++k){
          v[k]= u[x][k];
          A[k] = s[y][k];
          if(tb>t[y])
            A[k] += u[y][k]*(tb-t[y]);
          B[k] = s[x][k];
          if(tb>t[x])
            B[k] += u[x][k]*(tb-t[x]);
        }
        check(A, B, v, r[x], r[y], tb, tn);
        //case 2 both move
        if(t[y]<te[x]){
          tb=t[y]; tn=min(te[x], te[y]);
          for(int k=0;k<3;++k){
            v[k]= u[y][k] - u[x][k];
            A[k] = s[x][k];
            if(tb>t[x])
              A[k] += u[x][k]*(tb-t[x]);
            B[k] = s[y][k];
            if(tb>t[y])
              B[k] += u[y][k]*(tb-t[y]);
            check(A, B, v, r[x], r[y], tb, tn);
          }
          //case 3
          if(te[x] < te[y]){
            tb = max(te[x], (double)t[y]);
            tn = te[y];
            for(int k=0;k<3;++k){
              v[k]= u[y][k];
              A[k] = s[x][k];
              if(tb>t[x])
                A[k] += u[x][k]*(tb-t[x]);
              B[k] = s[y][k];
              if(tb>t[y])
                B[k] += u[y][k]*(tb-t[y]);
            }
            check(A, B, v, r[x], r[y], tb, tn);
          }   
          else{
            tb = te[y];
            tn = te[x];
            for(int k=0;k<3;++k){
              v[k] = u[x][k];
              A[k] = s[y][k];
              if(tb>t[y])
                A[k] += u[y][k]*(tb-t[y]);
              B[k] = s[x][k];
              if(tb>t[x])
                B[k] += u[x][k]*(tb-t[x]);
            }       
            check(A, B, v, r[x], r[y], tb, tn);
          }
        }
      }
    //output
    if(ans<0)
      printf("Never\n");
    else
      printf("%.2lf\n",ans+eps);
  }
  return 0;
}
