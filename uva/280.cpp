#include<stdio.h>
int n,v[1000],c[1000][1000];
void go(int p){
    for(int i=0;i<n;i++)
        if(c[p][i] && !v[i]){
            v[i]=1;
            go(i);
        }

}
main(){
int i,j,r,s;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    while(scanf("%d",&i) && i--)
        while(scanf("%d",&j) && j--)c[i][j]=1;
    scanf("%d",&s);
    while(s--){
        scanf("%d",&j);
        for(i=0;i<n;i++)v[i]=0;
        go(--j);
        for(r=i=0;i<n;i++)r+=!v[i];
        printf("%d",r);
        for(i=0;i<n;i++)
            if(!v[i])printf(" %d",i+1);
        puts("");
    }
}
}
