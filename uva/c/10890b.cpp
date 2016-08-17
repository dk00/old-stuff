#include<stdio.h>
#include<stdlib.h>
#define Min(a,b) (a)<(b)?(a):(b)
#define Max(a,b) (a)>(b)?(a):(b)
int n,t,s,min,use[50],px[50],py[50],map[50][50],c[50][50],best[30],path[30];
int inline num(int x1,int y1,int x2,int y2){
    return map[x2][y2]+map[x1-1][y1-1]-map[x2][y1-1]-map[x1-1][y2];
}
int inline dis(int x1,int y1,int x2,int y2){
	return abs(x1-x2)+abs(y1-y2);
}
void inline go(int d,int p,int q){
	if(d>=s){
        if(min>q+dis(px[p],py[p],n,n)){
            for(d=0;d<s;d++)
                best[d]=path[d];
        }
        min<?=q+dis(px[p],py[p],n,n);
    }
	if(min<=q+dis(px[p],py[p],n,n))return;
	for(int i=1;i<=t;i++)
		if(c[p][i] && use[i]){
            path[d]=i;
			use[i]--;
			go(d+1,i,q+dis(px[p],py[p],px[i],py[i]));
			use[i]++;
		}
}
int main(){
int i,j,C=1;
freopen("10890.in","r",stdin);
freopen("10890b.out","w",stdout);
while(scanf("%d %d %d",&n,&t,&s) && n+t+s){
    for(i=0;i<=n;i++)
        for(j=0;j<=n;j++)map[i][j]=0;
	for(i=0;i<=t+1;i++)
		for(j=0;j<=t+1;j++)c[i][j]=0;
    for(i=0;i<=t+1;i++)use[i]=1;
    for(i=1;i<=t;i++){
        scanf("%d %d",&px[i],&py[i]);
		px[i]++,py[i]++;
		map[px[i]][py[i]]++;
    }
	px[0]=1,py[0]=1,px[t+1]=n,py[t+1]=n;
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            map[i][j]+=map[i-1][j];
    for(i=1;i<=n;i++)
        for(j=1;j<=n;j++)
            map[i][j]+=map[i][j-1];
	for(i=1;i<=t;i++)
		if(num(1,1,px[i],py[i])==1+map[1][1])
			c[0][i]=1;
    int ww;
	for(i=1;i<=t;i++)
		for(j=1;j<=t;j++){
            ww=num(px[i]<?px[j],py[i]<?py[j],px[j]>?px[i],py[j]>?py[i]);
			if((px[i]<=px[j] || py[i]<=py[j])&& ww==2)
				c[i][j]=1;
        }
	min=n*n;
	go(0,0,0);
	printf("Case %d: %d\n",C++,min);
	for(i=0;i<s;i++)printf("%3d",best[i]);
	puts("");
}
}
