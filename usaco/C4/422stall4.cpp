/*
ID: s0000151
PROG: stall4
LANG: C++
*/
#include<stdio.h>
int i,j,t,sum,mm[402][402],path[402],use[402],to[402];
int dijkxtra(int s){
    for(i=1;i<=t;i++){
        use[i]=0;
        path[i]=s;
        to[i]=mm[s][i];
    }
    while(!to[t]){
        for(i=1;i<t && use[i] || !to[i];i++);
        if(i>=t)return 0;
        use[i]=1;
        for(j=1;j<=t;j++)
            if(!to[j] && mm[i][j]){
                path[j]=i;
                to[j]=1;
            }
    }
    if(!to[t])return 0;
    sum++;
    for(j=0,i=t;;i=path[i]){
        use[j++]=i;
        mm[i][path[i]]=1;
        mm[path[i]][i]=0;
        if(path[i]==s)break;
    }
    printf("0");
    while(j--)printf(" -> %d",use[j]);
    puts("");
}
main(){
freopen("stall4.in","r",stdin);
freopen("stall4.out","w",stdout);
int n,m,s;
scanf("%d %d",&n,&m);
for(i=1;i<=n;i++)mm[0][i]=1;
for(i=1;i<=m;i++)mm[i+n][n+m+1]=1;
for(i=1;i<=n;i++){
    scanf("%d",&s);
    while(s--){
        scanf("%d",&j);
        mm[i][n+j]=1;
    }
}t=n+m+1;
while(dijkxtra(0));
printf("%d\n",sum);
}
