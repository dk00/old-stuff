#include<stdio.h>
int n,v[100],c[100][100];
int work(int p){
    if(v[p])return 0;
    v[p]=1;
    int i,sum=1;
    for(i=0;i<n;i++)
        if(c[p][i])sum+=work(i);
    return sum;
}
main(){
int i,j,t,p,max;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    for(i=0;i<n;i++){
        scanf("%d",&t);
        while(t--){
            scanf("%d",&j);
            c[i][j-1]=1;
        }
    }
    for(i=max=0;i<n;i++){
        for(j=0;j<n;j++)v[j]=0;
        p=work(i);
        if(p>max){
            max=p;
            t=i;
        }
    }
    printf("%d\n",t+1);
}
}
