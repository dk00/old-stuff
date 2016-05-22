#include <stdio.h>

int main(void)
{
  int a, b, cs=0;
  int pa[15], fa[15], pb[15], fb[15], na, nb;
  while(scanf("%d%d",&a,&b)!=EOF && a>0) {
    ++cs;
    int i;
    na = nb = 0;
    for(i=2;i*i<=a;i++){
      if(a%i==0){
        pa[na] = i;
        fa[na] = 0;
        while(a%i==0){
          a/=i;
          ++fa[na];
        }
        ++na;
      }
    }
    if(a>1){pa[na] = a; fa[na++] = 1;}
    for(i=2;i*i<=b;i++){
      if(b%i==0){
        pb[nb] = i;
        fb[nb] = 0;
        while(b%i==0){
          b/=i;
          ++fb[nb];
        }
        ++nb;
      }
    }
    if(b>1){pb[nb] = b; fb[nb++] = 1;}
    int j=0, dst = 0, ord = 0;

    for(i=0;i<na;i++) {
      while(j < nb && pb[j] < pa[i]) {
        dst += fb[j];
        ord ++;
        ++j;
      }
      if(j<nb && pb[j]==pa[i]){
        ord ++;
        dst += (fb[j] > fa[i]? fb[j]-fa[i]:fa[i]-fb[j]);
        ++j;
      } else if(j==nb || (j<nb && pb[j] > pa[i])){
        ord++;
        dst += fa[i];
      }
    }
    while(j < nb) {
      dst += fb[j];
      ord++;
      ++j;
    }
    printf("%d. %d:%d\n", cs, ord, dst);
  }
  return 0;
}
