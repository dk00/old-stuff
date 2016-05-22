#include<stdio.h>
int use[51],possible;
void dfs(int d,int sum){
    if(possible)return;
    if(d>=5 && sum==23){
        possible=1;
        return;
    }
    for(int i=0;i<51;i++)
        if(use[i]){
            use[i]--;
            dfs(d+1,sum+i);
            dfs(d+1,sum-i);
            dfs(d+1,sum*i);
            use[i]++;
        }
}
void go(){
    for(int i=0;i<51;i++)
        if(use[i]){
            use[i]--;
            dfs(1,i);
            use[i]++;
            if(possible)return;
        }
}
main(){
int i,n1,n2,n3,n4,n5;
while(scanf("%d %d %d %d %d",&n1,&n2,&n3,&n4,&n5) && n1+n2+n3+n4+n5){
    for(i=0;i<=50;i++)use[i]=0;
    use[n1]++;use[n2]++;use[n3]++;use[n4]++;use[n5]++;
    possible=0;
    go();
    if(possible)puts("Possible");
    else puts("Impossible");
}
}
