#include<stdio.h>
int n,t,s,min,use[50],px[50],py[50],c[50][50],num[50][50],map[50][50];
int calc(int x1,int y1,int x2,int y2){
    if(x1>x2)x1^=x2^=x1^=x2;
    if(y1>y2)y1^=y2^=y1^=y2;
    return map[x2][y2]+map[x1-1][y1-1]-map[x2][y1-1]-map[x1-1][y2];
}
int dis(int x1,int y1,int x2,int y2){
    if(x1<x2)x1^=x2^=x1^=x2;
    if(y1<y2)y1^=y2^=y1^=y2;
    return x1-x2+y1-y2;
}
void go(int d,int p,int q){
    if(d>=s)min<?=(q+dis(px[p],py[p],n,n));
    if(min<=q+dis(px[p],py[p],n,n))return;
    for(int i=1;i<=t;i++)
        if(use[i] && c[p][i]){
            use[i]--;
            go(d+num[px[i]][py[i]],i,q+dis(px[p],py[p],px[i],py[i]));
            use[i]++;
        }
}
main(){
freopen("10890.in","r",stdin);
freopen("10890b.out","w",stdout);
px[0]=py[0]=1;
int i,j,C=1;
while(scanf("%d %d %d",&n,&t,&s) && n+t+s){
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)
            num[i][j]=map[i][j]=0;
    for(i=0;i<=t;i++)
        for(j=0;j<=t;j++)
            c[i][j]=0;
    for(i=1;i<=t;i++){
        scanf("%d %d",&px[i],&py[i]);
        px[i]++,py[i]++;
        num[px[i]][py[i]]++;
        use[i]=1;
    }
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            map[i][j]=num[i][j]+map[i-1][j];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            map[i][j]+=map[i][j-1];
    for(i=0;i<=t;i++)
        for(j=0;j<=t;j++)
            if(num[px[i]][py[i]]+num[px[j]][py[j]]==
            calc(px[i],py[i],px[j],py[j]))
                c[i][j]=1;
    min=n*n;
    go(num[1][1],0,0);
    printf("Case %d: %d\n",C++,min);
}
}
