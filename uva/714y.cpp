#include<stdio.h>
inline int max(int a,int b){return a>b?a:b;}
int s[501],d[501][501],p[501][501],r[501][501];
void print(int n,int k){
    if(k>1){
        print(p[k][n],k-1);
        printf(" /");
    }
    int i;
    if(k==1)printf("%d",s[1]);
    for(i=p[k][n]+1;i<=n;i++){
        printf(" %d",s[i]);
    }
}
main(){
int i,j,k,n,m,t,pg;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&n,&m);
    for(i=1;i<=n;i++)
        scanf("%d",&s[i]);
    for(i=1;i<=n;i++)
        for(k=1;k<=m;k++)
            d[k][i]=99999999;
    for(i=1;i<=n;i++){
        d[1][i]=d[1][i-1]+s[i];
        p[1][i]=1;
    }
    for(k=2;k<=m;k++)
        for(i=k-1;i<=n;i++)
            for(j=i+1,pg=0;j<=n;j++){
                pg+=s[j];
                if(max(pg,d[k-1][i])<d[k][j]){
                    p[k][j]=i;
                    d[k][j]=max(pg,d[k-1][i]);
                    r[k][j]=pg;
                }
            }
    print(n,m);
    puts("");
}
}
