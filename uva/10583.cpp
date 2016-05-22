#include<stdio.h>
int set[50000],d[50000];
main(){
int i,j,n,m,C=1;
while(scanf("%d %d",&n,&m) && n+m){
    for(i=0;i<n;i++){
        set[i]=i;
        d[i]=0;
    }
    while(m--){
        scanf("%d %d",&i,&j);
        i--,j--;
        while(i-set[i])i=set[i];
        while(j-set[j])j=set[j];
        if(i-j){
            if(d[i]>d[j]){
                set[j]=i;
                d[i]>?=(d[j]+1);
            }
            else{
                set[i]=j;
                d[j]>?=(d[i]+1);
            }
        }
    }
    for(i=j=0;i<n;i++)
        if(set[i]==i)j++;
    printf("Case %d: %d\n",C++,j);
}
}
