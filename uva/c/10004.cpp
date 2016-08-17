#include<stdio.h>
int p[201],link[201][201],n,bicolorable;
void dfs(int node){
    for(int i=0;i<n;i++){
        if(link[node][i]){
            if(p[i]==-1){
                p[i]=!(p[node]);
                dfs(i);
            }
            else bicolorable=(p[node]^p[i]);
        }
    }
}
main(){
int m,l1,l2;
while(scanf("%d",&n)){
    bicolorable=1;
    if(!n)break;
    scanf("%d",&m);
    for(l1=0;l1<n;l1++){
        p[l1]=-1;
        for(l2=0;l2<n;l2++)
            link[l1][l2]=0;
    }
    for(;m>0;m--){
        scanf("%d %d",&l1,&l2);
        link[l1][l2]=1;link[l2][l1]=1;
    }
    dfs(p[0]=0);
    if(!bicolorable)printf("NOT ");
    printf("BICOLORABLE.\n");
}
}
