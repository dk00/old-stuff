#include<stdio.h>
int n,r,find,use[2050],s[2050],path[1025];
void go(int d,int sum){
    if(find)return;
    if(d==n){
        if(sum%n==0){
            find=1;
            printf("%d",s[path[0]]);
            for(d=1;d<n;d++)
                printf(" %d",s[path[d]]);
            puts("");
        }
        return;
    }
    for(int i=0;i<r && !find;i++)
        if(use[i]){
            use[i]=0;
            path[d]=i;
            go(d+1,sum+s[i]);
            use[i]=1;
        }
}
main(){
int i;
while(scanf("%d",&n) && n){
    r=2*n-1;
    for(find=i=0;i<r;i++){
        scanf("%d",&s[i]);
        use[i]=1;
    }
    puts("Yes");
    go(0,0);
}
}
