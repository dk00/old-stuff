#include<stdio.h>
#include<stdlib.h>
int n,r,sum,find,s[2500],use[2500],dp[1025000];
int numcmp(const void *a,const void *b){
    return *(int *)b-*(int *)a;
}
void dfs(int d,int s,int i){
    if(find)return;
    if(d>=n){
        if(!s){
            find=1;
            for(i=0;i<r && use[i];i++);
            printf("Yes\n%d",s[i]);
            for(i++;i<r;i++)
                if(!use[i])printf(" %d",s[i]);
            puts("");
        }
        return;
    }
    while(s[i]>
    for(;i<r;i++)
        if(use[i]
    
}
main(){
int i,j,k;
while(scanf("%d",&n) && n){
    r=(n<<1)-1;
    for(k=0;k<=1024000;k++)dp[k]=0;
    dp[0]=1;
    for(find=sum=i=0;i<r;i++){
        scanf("%d",&s[i]);
        sum+=s[i];
        for(k=n-s[i];k>=0;k--)
            if(dp[k])dp[k+s[i]]=1;
    }
    for(i=n;i<=1024000;i++){
        if(dp[i])
            dfs(0,i,0);
    }
    if(!find)puts("No");
}
}
