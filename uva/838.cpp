#include<stdio.h>
int n,f,max,best,
num[1001],use[1001],us3[1001],map[13][13],ma2[13][13];
int dfs2(int x,int y){
    if(!use[map[x][y]] || ma2[x][y]==f)return 0;
    ma2[x][y]=f;
    int p=0,tmp=0;
    if(p+=(us3[map[x][y]]!=f))
        us3[map[x][y]]=f;
    if(x)tmp+=dfs2(x-1,y);
    if(y)tmp+=dfs2(x,y-1);
    if(x+1<n)tmp+=dfs2(x+1,y);
    if(y+1<n)tmp+=dfs2(x,y+1);
    if(p)us3[map[x][y]]=-1;
    return tmp+p;
}
void dfs1(int s,int x,int y){
    if(!use[map[x][y]])return;
    best>?=s;
    int ext=dfs2(x,y)-1;
    use[map[x][y]]=0;
    f++;
    if(s+ext<=best){
        use[map[x][y]]=1;
        return;
    }
    if(x)dfs1(s+1,x-1,y);
    if(y)dfs1(s+1,x,y-1);
    if(x+1<n)dfs1(s+1,x+1,y);
    if(y+1<n)dfs1(s+1,x,y+1);
    use[map[x][y]]=1;
}
main(){
int t,i,j;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    max=n*n;
    best=-1;
    for(i=0;i<=1000;i++){
        num[i]=0;us3[i]=-1;
        use[i]=1;
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            scanf("%d",&map[i][j]);
            ma2[i][j]=-1;
        }
    for(f=i=0;i<n;i++)
        for(j=0;j<n;j++)
            dfs1(1,i,j);
    printf("%d\n",best);
    if(t)puts("");
}
}
