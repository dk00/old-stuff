/*
ID: s0000151
PROG: schlnet
LANG: C++
*/
#include<stdio.h>
int n,r[100],v1[100],v2[100],u1[100],u2[100],c[100][100];
void dfs1(int p){
    v1[p]=r[p]=1;
    v2[p]=0;
    for(int i=0;i<n;i++)
        if(c[p][i] && !r[i])
            dfs1(i);
}
void dfs2(int p){
    u1[p]=r[p]=1;
    u2[p]=0;
    for(int i=0;i<n;i++)
        if(c[i][p] && !r[i])
            dfs2(i);
}
main(){
freopen("schlnet.in","r",stdin);
freopen("schlnet.out","w",stdout);
scanf("%d",&n);
int i,j,a,b;
for(i=0;i<n;i++)
    while(scanf("%d",&j) && j)
        c[i][j-1]=1;
for(i=0;i<n;i++){
    if(!v1[i]){
        for(j=0;j<n;j++)r[j]=0;
        dfs1(i);
        v2[i]=1;
    }
    if(!u1[i]){
        for(j=0;j<n;j++)r[j]=0;
        dfs2(i);
        u2[i]=1;
    }
}
for(a=b=i=0;i<n;i++){
    a+=v2[i];
    b+=u2[i];
}
printf("%d\n%d\n",a,(a>?b)*!(a==1 && b==1 && v2[0]==1 && u2[0]==1));
}
