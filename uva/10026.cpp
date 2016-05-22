#include<stdio.h>
#include<stdlib.h>
struct Work{
    int day,money,oid;
    void get(){scanf("%d %d",&day,&money);}
}work[1000];
int workcmp(const void *a,const void *b){
    return((((Work *)b)->money)*(((Work *)a)->day)-
    (((Work *)a)->money)*(((Work *)b)->day))
    ;
}
main(){
int i,n,t;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++){
        work[i].get();
        work[i].oid=i+1;
    }
    qsort(work,n,sizeof(*work),workcmp);
    printf("%d",work->oid);
    for(i=1;i<n;i++)printf(" %d",work[i].oid);
    puts(t?"\n":"");
}
}
