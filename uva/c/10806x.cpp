#include<stdio.h>
int n,p[100],to[100],c[100][100],s[100][100];
int push(int v){
    if(p[v]<0)return 0;
    c[p[v]][v]--;
    c[v][p[v]]++;
    s[p[v]][v]*=-1;
    s[v][p[v]]*=-1;
    return s[p[v]][v]*-1+push(p[v]);
}
int path1(){
int i,j;
    for(i=0;i<n;i++)
        if(c[0][i]){
            p[i]=0;
            to[i]=s[0][i];
        }
        else p[i]=i;
    to[0]=0;
    p[0]=-1;
    while(p[n-1]==n-1){
        for(i=0;!to[i] && i<n;i++);
        if(i>n)break;
        for(j=i+1;j<n;j++)
            if(to[j] && to[j]<to[i])i=j;
        for(j=0;j<n;j++)
            if(c[i][j] && (p[j]==j || s[i][j]+to[i]<to[j]){
                p[j]=i;
                to[j]=to[i]+s[i][j];
            }
        to[i]=0;
    }
    if(p[n-1]==n-1)return 0;
    push(n-1);
    return 1;
}
int path2(){
int i,j,k;
    for(i=0;i<n;i++)p[i]=i;
    p[0]=-1;
    to[0]=0;
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            if(p[i]-i)
                for(j=0;j<n;j++)
                    if(c[i][j] && (p[j]==j || s[i][j]+to[i]<to[j]){
                        p[j]=i;
                        to[j]=to[i]+s[i][j];
                    }
    if(p[n-1]==n-1)return 0;
    return push(n-1);
}
main(){
int i,j,k,m,min;
while(scanf("%d",&n) && n){
    scanf("%d",&m);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        c[i][j]=c[j][i]=1;
        s[i][j]=s[j][i]=k;
    }
    if(path1() && min=path2())printf("%d\n",min);
    else puts("Back to jail");
}
