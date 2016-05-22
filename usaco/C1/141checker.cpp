/*
ID: s0000151
PROG: checker
LANG: C++
*/
#include<stdio.h>
int row[13]={1,1,1,1,1,1,1,1,1,1,1,1,1}
,col[13]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
,rc[25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
,cr[25]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
,soln=0,n,c;
//long long d1=0,d2=0;
void dfs2(){
    //d2++;
    if(c>=n){soln++;return;}
    int r;
    for(r=0;r<n;r++){
        for(;r<n && (row[r]+rc[n+r-c-1]+cr[r+c])<3;r++);
        if(r>=n)return;
        rc[n+r-c-1]=0;cr[r+c]=0;
        row[r]=0;col[c++]=r;
        dfs2();
        c--;
        rc[n+r-c-1]=1;cr[r+c]=1;
        row[r]=1;
    }
}
void dfs(){
    //d1++;
    if(c>=n){
        if(++soln<=3){
        printf("%d",col[0]+1);
        for(c=1;c<n;c++)
            printf(" %d",col[c]+1);
        printf("\n");
        }
        return;
    }
    for(int r=0;r<n;r++){
        for(;r<n && (row[r]+rc[n+r-c-1]+cr[r+c])<3;r++);
        if(r>=n)return;
        rc[n+r-c-1]=0;cr[r+c]=0;
        row[r]=0;col[c++]=r;
        if(soln>=3)dfs2();
        else dfs();
        c--;
        if(!c && r+1==n/2 && n>6)soln*=2;
        if(!c && r==(n-1)/2 && n>6)return;
        rc[n+r-c-1]=1;cr[r+c]=1;
        row[r]=1;
    }
}
main(){
int i;
/*freopen("checker.in","r",stdin);
freopen("checker.out","w",stdout);*/
while(scanf("%d",&n)==1){;c=0;
dfs();
printf("%d\n",soln);}
//printf("%I64d %I64d\n",d1,d2);
//scanf(" ");
}
