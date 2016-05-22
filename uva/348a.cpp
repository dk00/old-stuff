#include<stdio.h>
int d[15],s[15][15],p[15][15],cut[15][15];
inline void show(int l,int r){
    if(l==r){
        printf("A%d",l+1);
        return;
    }
    putchar('(');
    show(l,p[l][r]);
    printf(" x ");
    show(p[l][r]+1,r);
    putchar(')');
}
inline int mul(int l,int r){
    if(l==r)return 0;
    int i,m;
    s[l][r]=2147483647;
    for(i=l;i<r;i++){
        m=mul(l,i)+mul(i+1,r)+d[l]*d[i+1]*d[r+1];
        if(m<s[l][r]){
            s[l][r]=m;
            p[l][r]=i;
        }
    }
    cut[l][r]=1;
    return s[l][r];
}
main(){
int i,j,n,C=1;
while(scanf("%d",&n) && n){
    scanf("%d",d);
    for(i=1;i<n;i++)scanf("%d",&d[i]),scanf("%d",&d[i]);
    scanf("%d",&d[i]);
    for(i=0,n;i<n;i++)
        for(j=0;j<n;j++)
            cut[i][j]=0;
    mul(0,n-1);
    printf("Case %d: ",C++);
    show(0,n-1);
    puts("");
}
}
