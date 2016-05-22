/*
ID: s0000151
PROG: picture
LANG: C++
*/
#include<stdio.h>
int n,sum,rect1[5000],rect2[5000],rect3[5000],rect4[5000],used[5000];
void dfs(int d,int i,int r,int sx,int sy,int ex,int ey){
    sum+=(ex-sx+ey-sy)*r;
    for(;i<n;i++){
        if(rect1[i]>ex||rect2[i]>ey||rect3[i]<sx||rect4[i]<sy)
            continue;
        dfs(d+1,i+1,-1*r,sx>?rect1[i],sy>?rect2[i],
        ex<?rect3[i],ey<?rect4[i]);
    }
}
main(){
freopen("picture.in","r",stdin);
freopen("picture.out","w",stdout);
int i;
scanf("%d",&n);
for(i=0;i<n;i++)
    scanf("%d %d %d %d",&rect1[i],&rect2[i],&rect3[i],&rect4[i]);
for(i=0;i<n;i++)
    dfs(0,i+1,2,rect1[i],rect2[i],rect3[i],rect4[i]);
printf("%d\n",sum);
}
