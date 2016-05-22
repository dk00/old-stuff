#include<stdio.h>
int n,path[16],isp[35],use[17];
void go(int d){
    if(d>=n){
        if(isp[path[n-1]+path[0]]){
            putchar('1');
            for(d=1;d<n;d++)
                printf(" %d",path[d]);
            puts("");
        }
        return;
    }
    for(int i=2;i<=n;i++)
        if(use[i] && isp[path[d-1]+i]){
            use[i]--;
            path[d]=i;
            go(d+1);
            use[i]++;
        }
}
main(){
int i,j,C=0;
for(i=3;i<35;i++,i++){
    isp[i]=1;
    for(j=2;j<=i/j;j++)
        if(i%j==0)isp[i]=0;
}
path[0]=1;
while(scanf("%d",&n)!=EOF){
    for(i=2;i<=n;i++)use[i]=1;
    if(C++)puts("");
    printf("case %d:\n",C);
    go(1);
}
}
