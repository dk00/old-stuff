#include <stdio.h>

double a[105][105];
double b[105];

double f[105][105];
double tr[105][105];
int ids[105];
int id[105];

int abs(int x){
  return x<0? -x:x;
}
bool nonzero(double x){
  return x<-1e-8 || x>1e-8;
}

int main(void)
{
  int w, h, d, i, j, k, l, cs=0;
  while(scanf("%d%d%d",&w,&h,&d)!=EOF && w>0){
    if(++cs>1) printf("\n");
    for(i=0;i<h;i++)
      for(j=0;j<w;j++){
        scanf("%lf",&f[i][j]);
      }
    for(i=0;i<h;i++)
        for(j=0;j<w;j++)
          tr[i][j] = 0.0;
    for(i=0;i<h;i++)
      for(j=0;j<w;j++)
        for(k=0;k<h;k++)
          for(l=0;l<w;l++)
            if(abs(i-k)+abs(j-l)<=d){
              tr[i][j] += 1.0;
              a[i*w+j][k*w+l] = 1.0;
            }else
              a[i*w+j][k*w+l] = 0.0;
    for(i=0;i<h;i++)
      for(j=0;j<w;j++){
        b[i*w+j] = f[i][j] * tr[i][j];
        ids[i*w+j] = i*w+j;
      }
    for(i=0;i<h*w;i++){
      for(j=i;j<h*w;j++)
        if(nonzero(a[j][i]))
          break;
      if(j!=i){
        for(k=0;k<h*w;k++)
        {double t = a[j][k];a[j][k] = a[i][k];a[i][k] = t;}
        double t=b[i];b[i]=b[j];b[j]=t;
        int tmp = ids[i];ids[i]=ids[j];ids[j]=tmp;
      }
      b[i] /= a[i][i];
      for(j=h*w-1;j>=i;j--){
        a[i][j] /= a[i][i];
      }
      for(j=i+1;j<h*w;j++){
        b[j] = b[j] - b[i]*a[j][i];
        for(k=h*w-1;k>=i;k--)
          a[j][k] = a[j][k] - a[i][k]*a[j][i];
      }
    }
    double ans[15][15];
    for(i=h*w-1;i>=0;i--){
      for(j=i+1;j<w*h;j++)
        b[i] -= b[j] * a[i][j];
      //ans[ids[i]/w][ids[i]%w] = b[i];
      ans[i/w][i%w] = b[i];
      //printf("%d=>%lf\n", ids[i], b[i]);
    }
    for(i=0;i<h;i++,printf("\n"))
      for(j=0;j<w;j++)
        printf("%8.2lf",ans[i][j]);
  }
  return 0;
}
