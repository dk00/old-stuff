#include <stdio.h>

int a[40], rsub[40], rend[40];
int x, m;
int exist(){
  int mx, y, z;
  mx = x;
  if(x < 0) return false;
  if(a[x]==0) return true;
  if(a[x] == 1){
    --x;
    y = exist();
    rsub[mx] = --x;
    z = exist();
    rend[mx] = x;
  }
  return y && z;
}

int fill(int L,int R){
  if(L>R) return 0;
  if(L==R){
    a[L] = 0;
  }else{
    if((R-L)%2==1) fprintf(stderr, "WARNING!\n");
    else{
      a[R] = 1;
      a[R-1] = 0;
      fill(L, R-2);
    }
  }
  return 0;
}

int next(int reserve){
  //fprintf(stderr,"x = %d\n", x);
  int mx = x, y, z;
  //fprintf(stderr,"a[%d]=%d, rsub=%d, rend=%d\n", x, a[mx], rsub[x], rend[x]);
  if(a[mx] == 0){
    if(mx-2 >= reserve){
     // printf("here at %d\n", mx);
      a[mx] = 1;
      a[mx-1] = 0;
      a[mx-2] = 0;
      return mx - 2;
    }
    return -1;
  }
  x = rsub[mx];
  y = next(reserve);
  //fprintf(stderr,"y = %d\n", y);
  if(y != -1) return y;
  x = mx - 1;
  z = next(reserve + 1);
//  fprintf(stderr, "z = %d\n", z);
  if (z == -1) return -1;
  if (reserve > 0){
    a[z-1] = 0;
    return z-1;
  } else {
    fill(0, z-1);
    return 0;
  }
  /*if(z > rend[mx]){
    fill(rend[mx], z-1);
    return rend[mx];
  }*/
  return z;
}

int main(void)
{
  int i, T;
  scanf("%d", &T);
  while(T--){
    int n;
    scanf("%d", &n);
    int t = n;
    m = 0;
    if(n==0){
      printf("0\n");
      continue;
    }
    while(t>0){
      a[m++] = t%2;
      t/=2;
    }
    --m;
    x = m;

   // for(i=m;i>=0;i--)
     // printf("%d", a[i]);
//    printf("\n");
    if(!exist() || x != 0)
      printf("NO\n");
    else {
      x = m;
      int z = next(0);
      if (z == -1){
        int ans = 0;
        for(i=m;i>0;i-=2){
          ans += (1<<i);
        }
        printf("%d\n", ans);
      }else{
        int ans = 0;
        for(i=m;i>=0;i--){
         ans = ans * 2 + a[i];
        }
       
        printf("%d\n", ans);
      }
    }
  }
  return 0;
}
