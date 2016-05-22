/*
ID: s0000151
PROG: milk6
LANG: C++
*/
#include<stdio.h>
#define Min(a,b) (a)<(b)?(a):(b)
int n,max,lft,find,e[32],h[32],c[32][32],used[1000];
void push(int v,int u){
    find=1;
int f=Min(c[v][u],e[v]);
    //printf("push %d -> %d : %d\n",v+1,u+1,f);
    c[v][u]-=f;
    c[u][v]+=f;
    e[v]-=f;
    e[u]+=f;
}
void relabel(int v){
int i,min=n*3;
    for(i=0;i<n;i++)
        if(c[v][i]>0){
            if(h[v]==h[i]+1)return;
            else min=Min(h[i]+1,min);
        }
    if(min>n*2)return;
    //printf("relabel %d -> %d(+%d)\n",v+1,min,min-h[v]);
    h[v]=min;
    find=1;
}
int flow(){
int i,j,k;
    for(i=0;i<n;i++)h[i]=e[i]=0;
    h[0]=n;
    //preflow
    for(i=1;i<n;i++)
        if(c[0][i]>0){
            e[i]=c[0][i];
            c[i][0]=c[0][i];
            c[0][i]=0;
        }
    do{
        //find pushable node
        for(find=0,i=1;i<n-1;i++)
            if(e[i]>0)
                for(j=0;j<n;j++)
                    if(h[i]==h[j]+1 && c[i][j]>0)
                        push(i,j);
        for(i=1;i<n-1;i++)
            if(e[i]>0)
                relabel(i);
    }while(find);
    max=max>e[n-1]?max:e[n-1];
    return e[n-1];
}
main(){
freopen("milk6.in","r",stdin);
freopen("milk6.out","w",stdout);
int i,j,m,f1,f2,cn=0,o[32][32],cut[1000],from[1000],to[1000],num[1000];
scanf("%d %d",&n,&m);
for(i=0;i<n;i++)
    for(j=0;j<n;j++)
        o[i][j]=0;
for(i=0;i<m;i++){
    scanf("%d %d %d",&from[i],&to[i],&num[i]);
    o[--from[i]][--to[i]]+=num[i];
    cut[i]=0;
}
for(i=0;i<n;i++)
    for(j=0;j<n;j++)
        c[i][j]=o[i][j];/*
flow();
puts("---------test output---------");
for(i=0;i<m;i++)
    printf("%d %d %d\n",from[i]+1,to[i]+1,c[from[i]][to[i]]);
puts("---------test output---------");
for(i=0;i<n;i++)
    for(j=0;j<n;j++)
        c[i][j]=o[i][j];*/
while(1){
    f1=flow();
    if(f1<=0)break;
    for(i=0;c[from[i]][to[i]]+used[i];i++);
    for(lft=i;i<m;i++)
        if(!c[from[i]][to[i]] && num[i]>num[lft] && !used[i])
            lft=i;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=o[i][j];
    c[from[lft]][to[lft]]-=num[lft];
    used[lft]=1;
    f2=flow();
    if(f1-f2==num[lft]){
        cut[lft]=1;
        cn++;
        o[from[lft]][to[lft]]-=num[lft];
        for(i=0;i<m;i++)used[i]=cut[i];
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=o[i][j];
}
printf("%d %d\n",max,cn);
for(i=0;i<m;i++)if(cut[i])printf("%d\n",i+1);
}
