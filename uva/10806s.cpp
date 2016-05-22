#include<stdio.h>
int push(int v){
    if(p[v]<0)return 0;
    c[p[v]][v]--;
    c[v][p[v]]++;
    return s[p[v]][v]+push(p[v]);
}
void bfs(){
int i,j,k;
    for(i=0;i<n;i++)p[i]=i;
    p[0]=-1;
    to[0]=0;
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            if(p[i]!=i)
                for(j=0;j<n;j++)
                    if(c[i][j] && (p[j]==j || to[j]<to[i]+s[i][j]){
                        p[j]=i;
                        to[j]=s[i][j];
                    }
    if(p[n-1]==n-1)return 0;
    return push(n-1);
}
int dijkstra(){
int i,j,k;
    for(i=0;i<n;i++){
        if(c[0][i]){
            to[i]=s[0][i];
            p[i]=0;
        }
        else{
            p[i]=i;
            to[i]=0;
        }
    }
    to[0]=0;
    p[0]=-1;
    while(1){
        for(i=0;!to[i] && i<n;i++);
        if(i>=n)return;
        for(j=i+1;j<n;j++)
            if(to[j] && to[j]<to[i])i=j;
        for(j=0;j<n;j++)
            if(c[i][j] && (p[j]==j || to[i]+s[i][j]<to[j]){
                to[j]=to[i]+s[i][j];
                p[j]=i;
            }
        to[i]=0;
    }
    return push(n-1);
}
main(){
while(scanf("%d",&n && n){
    scanf("%d",&m);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        s[i][j]=s[j][i]=k;
        c[i][j]=c[j][i]=1;
    }
    if(dijkstra() && min=bfs())printf("%d\n",min);
    else puts("Back to jail");
}
}
