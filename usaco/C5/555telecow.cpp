/*
ID: s0000151
PROG: telecow
LANG: C++
*/
#include<stdio.h>
int n,s,t,rep,pup,h[200],e[200],out[200],
rel[200],pus[200][2],c[200][200],o[200][200];
void push(int p){
int v=pus[p][0],u=pus[p][1],f=(e[v]<?c[v][u]);
    if(!f)return;
    e[v]-=f;
    e[u]+=f;
    c[v][u]-=f;
    out[v]-=f;
    c[u][v]+=f;
    out[u]+=f;
    if(f && u!=t && u!=s)rel[rep++]=u;
    if(u!=s && u!=t && e[v] && out && (!p || pus[p-1][0]!=v))
        rel[rep++]=v;
    printf("push %d -> %d(%d)\n",v+1,u+1,f);
}
void relabel(int v){
int i,j,min=n;
    for(j=i=0;i<n;i++){
        if(v==i)continue;
        if(c[v][i] && h[i]+1<min){
            min=h[i]+1;
            pus[pup][0]=v;
            pus[pup][1]=i;
            j=1;
        }
        else if(c[v][i] && h[i]+1==min){
            pus[pup+j][0]=v;
            pus[pup+j++][1]=i;
        }
    }
    h[v]=min;
    pup+=j;
    printf("relabel %d(%d)\n",v+1,min);
}
int flow(){
    puts("----------------------------------------");
int i,j;
    for(i=0;i<n;i++){
        h[i]=e[i]=0;
        for(out[i]=j=0;j<n;j++)
            out[i]+=(c[i][j]=o[i][j]);
    }
    for(rep=pup=i=0;i<n;i++){
        if(i==s || !c[s][i])continue;
        e[i]+=c[s][i];
        c[i][s]+=c[s][i];
        out[s]-=c[s][i];
        c[s][i]=0;
        rel[rep++]=i;
    }
    h[s]=n;
    while(rep+pup){
        while(pup)push(--pup);
        while(rep)relabel(rel[--rep]);
    }
    return e[t];
}
main(){
freopen("telecow.in","r",stdin);
freopen("telecow.out","w",stdout);
int i,j,m,f1,f2,sn=200000;
scanf("%d %d %d %d",&n,&m,&s,&t);
s--,t--;
for(i=0;i<n;i++)
    o[i][i+n]=o[i+n][i]=1;
while(m--){
    scanf("%d %d",&i,&j);
    i--,j--;
    o[i+n][j]=sn;
    o[j+n][i]=sn;
}
t+=n,m=n,n<<=1;
o[s][s+m]=o[t-m][t]=sn;
printf("%d\n",f1=flow());
for(i=0;i<m && f1;i++){
    if(i==s || i==t-m)continue;
    o[i][i+m]=o[i+m][i]=0;
    f2=flow();
    if(f1>f2)
        printf("%d%c",i+1,(f1=f2)?' ':'\n');
    else o[i][i+m]=o[i+m][i]=1;
}
}
