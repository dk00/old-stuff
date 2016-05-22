#include<stdio.h>
int n,s,t,min,c[100][100],p[100],q[100];
void go(int v){
    min<?=c[p[v]][v];
    if(p[v]-s)go(p[v]);
    c[p[v]][v]-=min;
    c[v][p[v]]+=min;
}
int findpath(){
int i,j,k;
    min=100000000;
    for(k=0;k<n;k++)p[k]=-1;
    p[s]=q[0]=s;
    for(i=0,j=1;i<j && p[t]<0;i++)
        for(k=0;k<n;k++)
            if(c[q[i]][k] && p[k]<0)p[q[j++]=k]=q[i];
    if(p[t]>=0)go(t);
    else return 0;
    return min;
}
int flow(){
    int total=0,f;
    while((f=findpath()))total+=f;
    return total;
}
main(){
int i,j,k,C,N=1;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    scanf("%d %d %d",&s,&t,&C);
    s--,t--;
    while(C--){
        scanf("%d %d %d",&i,&j,&k);
        c[i-1][j-1]+=k;
        c[j-1][i-1]+=k;
    }
    printf("Network %d\n",N++);
    printf("The bandwidth is %d.\n\n",flow());
}
}
