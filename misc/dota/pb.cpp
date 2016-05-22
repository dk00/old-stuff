#include<algorithm>
int tr[10001],i,j,n,m,ma1,ma2;
main(){
  while(scanf("%d %d",&n,&m)&&n+m!=0){
    ma1=ma2=0;
    memset(tr,0,sizeof(tr));
    for(i=0;i<n*m;i++){
      scanf("%d",&j);
      tr[j]++;
    }
    for(i=1;i<=10000;i++){
      if(tr[i]>ma1){
        ma2=ma1;
        ma1=tr[i];
      }
      else if(tr[i]>=ma2)ma2=tr[i];
    }
    for(i=1,j=0;i<=10000;i++){
      if(tr[i]==ma2){
        if(j==1)printf(" ");
        printf("%d",i);
        j=1;
      }
    }
    puts("");
  }
}
