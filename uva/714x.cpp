#include<stdio.h>
int inline min(int a,int b){return a<b?a:b;}
int inline max(int a,int b){return a>b?a:b;}
int g[500],s[500][501],r[500][501],p[500][501];
void print(int n,int k){
    if(!n){
        printf("%d",g[0]);
        return;
    }
    if(!p[n][n])print(n-1,k);
    else{
        print(n-1,k-1);
        printf(" /");
    }
    printf(" %d",g[n]);
}
main(){
int i,j,n,k,t;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++)
        scanf("%d",&g[i]);
    s[0][1]=g[0];
    r[0][1]=g[0];
    p[0][1]=-1;
    for(i=1;i<n;i++)
        for(j=1;j<=k && j+1<=i;j++){
            if(j==1||max(r[i-1][j]+g[i],s[i-1][j])<max(s[i-1][j-1],g[i]))
                r[i][j]=r[i-1][j]+g[i],
                s[i][j]=max(r[i-1][j]+g[i],s[i-1][j]),
                p[i][j]=0;
            else
                r[i][j]=g[i],
                s[i][j]=max(s[i-1][j-1],g[i]),
                p[i][j]=1;
        }
    print(n-1,k);
    puts("");
}
}
