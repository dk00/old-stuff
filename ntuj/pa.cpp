#include <stdio.h>
#include <algorithm>

long long a[5005], b[5005], tmp[5005];
long long p[5005][4], np=0;
inline long long abs(long long x) {
  return x<0? -x: x;
}
void resort(void) {
  long long L = p[np-1][2], R = p[np-1][3], M=0;
  long long i, t;
//    printf("> %lld\n", p[0][2]);
  for(i=R;i>L;i--) {
    if(b[i] < b[i-1]) {
      t = b[i]; b[i] = b[i-1]; b[i-1] = t;
    } else
      break;
  }
  M = (L+R)/2;
  long long d = 0;
  p[np-1][0] = b[M]/* - (M-L)*/;
  p[np-1][1] = b[M]/* + (R-M)*/;
}
void merge(void) {
//  printf("np=%d, [%d, %d], [%d, %d]\n",np, p[np-1][2], p[np-1][3], 
//      p[np-2][2], p[np-2][3]);
//    printf("> %lld\n", p[0][2]);
  p[np-2][3] = p[np-1][3];
  long long i, j, L = p[np-2][2], R = p[np-2][3], M = p[np-1][2];
  i=L, j=M;
  long long k = L;
  while(i<M || j<=R) 
  {
    if(i>=M || j<=R && b[i] > b[j]) tmp[k++] = b[j++];
    else tmp[k++] = b[i++];
  }
  for(i=L;i<=R;i++)
    b[i] = tmp[i];
  M = (L+R)/2;
  --np;
  p[np-1][0] = b[M]/*-(M-L)*/;
  p[np-1][1] = b[M]/*+(R-M)*/;
 // printf("(%d, %d, %d, %d)\n", p[np-1][0], p[np-1][1], p[np-1][2], p[np-1][3]);
}

int main(void) {
  long long T, n, i, j;
  scanf("%lld", &T);
  while(T--){
    scanf("%lld", &n);
    for(i=0;i<n;i++) {
      scanf("%lld", &a[i]);
      a[i] -= i;
      b[i] = a[i];
    }
    np=0;
    p[0][0] = a[0];
    p[0][1] = a[0];
    p[0][2] = 0;
    p[0][3] = 0;
    np=1;
    for(i=1;i<n;i++) {
      //printf("np=%d %lld\n", np, a[i]);
      //printf("p[%d][3]= %lld %lld\n",np-1,  p[np-1][2], p[np-1][3]);
      if(p[np-1][1] <= a[i]) {
        p[np][0] = a[i];
        p[np][1] = a[i];
        p[np][2] = i;
        p[np++][3] = i;
      } else {
        p[np-1][3] = i;
        resort();
        while(np>1 && p[np-1][0] <= p[np-2][1]) {
         // printf("np=%d\n", np);
         // puts("MERGE");
          merge();
          //printf("i=%lld\n", i);
          //printf("p[%d][3]= %lld %lld\n",0,  p[0][2], p[0][3]);
        }
      }
    }
    long long d[5005]={}, nd=0;
//    for(i=0;i<np;i++)
  //    printf("SEGMENT %lld %lld %lld %lld\n", p[i][0], p[i][1], p[i][2], p[i][3]);
    for(i=0;i<np;i++) {
      for(j=p[i][2]; j<=p[i][3]; j++) {
        d[j] = p[i][0] - a[j];
        //nd += abs(d[j]);
        //printf("nd=%d\n", nd);
      }
    }
    for(i=0;i<n;i++)
      b[i] = d[i];
    std::sort(b, b+n);
    long long mid = b[n/2];
    for(i=0;i<n;i++) {
      d[i] -= mid;
      nd += abs(d[i]);
    }
    printf("%lld\n", nd);
    for(i=0;i<n;i++)
      printf("%lld%c", d[i], i==n-1?'\n':' ');
  }
  return 0;
}
