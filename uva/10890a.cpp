#include<stdio.h>
#include<stdlib.h>
int t,s,min,v[32][2],c[32][32],path[12],best[12],use[32];
void go(int d,int p,int l){
    if(d==s+1){
        if(l+c[p][t+1]<min)
            for(d=0;d<s+1;d++)
                best[d]=path[d];
        min<?=(l+c[p][t+1]);
        return;
    }
    if(l+c[p][t+1]>=min)return;
    for(int i=1;i<=t;i++)
        if(use[i]){
            use[i]=0;
            path[d]=i;
            if(l+c[p][i]<min)go(d+1,i,l+c[p][i]);
            use[i]=1;
        }
}
main(){
int i,j,n,C=1;
freopen("10890.in","r",stdin);
freopen("10890a.out","w",stdout);
while(scanf("%d %d %d",&n,&t,&s) && t+n+s){
    v[0][0]=0;v[0][1]=0;
    v[t+1][0]=n-1;v[t+1][1]=n-1;
    for(i=1;i<=t;i++)
        scanf("%d %d",&v[i][0],&v[i][1]);
    for(i=0;i<=t+1;i++){
        use[i]=1;
        for(j=0;j<=t+1;j++)
            c[i][j]=abs(v[i][0]-v[j][0])+abs(v[i][1]-v[j][1]);
    }
    use[0]=0;
    min=10000000;
    path[0]=0;
    go(1,0,0);
    printf("Case %d: %d\n",C++,min);
    for(i=1;i<=s;i++)printf("%3d",best[i]);
    puts("");
}
}
