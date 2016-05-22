/*
ID: s0000151
PROG: cowtour
LANG: C++
*/
#include<stdio.h>
#include<math.h>
#define dis(x1,y1,x2,y2) ((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))
double dist[150][150],to[150],in[150],min=1e8,d;
int set[150],link[150][150],p,n;
void dfs(int t){
    if(set[t]>=0)return;
    set[t]=p;
    for(int i=0;i<n;i++)if(link[i][t])dfs(i);
}
main(){
freopen("cowtour.in","r",stdin);
freopen("cowtour.out","w",stdout);
char c,s[151];
int i,j,k,x[150],y[150];
scanf("%d%c",&n,&c);
for(i=0;i<n;i++){
    set[i]=-1;
    scanf("%d %d%c",&x[i],&y[i],&c);
}
for(i=0;i<n;i++){
    scanf("%s",s);
    for(j=0;j<n;j++){
        link[i][j]=s[j]-'0';
        if(link[i][j])dist[i][j]=sqrt(dis(x[i],y[i],x[j],y[j]));
        else dist[i][j]=1e10;
    }
    dist[i][i]=0;
}
for(p=i=0;i<n;i++)
    if(set[i]<0){
        dfs(i);
        p++;
    }
for(k=0;k<n;k++)
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            dist[i][j]<?=(dist[i][k]+dist[k][j]);
for(i=0;i<n;i++){
    for(j=0;j<n;j++)
        if(dist[i][j]<1e10)to[i]>?=dist[i][j];
    in[set[i]]>?=to[i];
}
for(i=0;i<n;i++)
    for(j=0;j<n;j++){
        if(set[i]==set[j])continue;
        d=to[i]+to[j]+sqrt(dis(x[i],y[i],x[j],y[j]));
        d>?=(in[set[i]]>?in[set[j]]);
        min<?=d;
    }
printf("%.6lf\n",min);
}

