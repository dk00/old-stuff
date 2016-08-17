#include<stdio.h>
int n,p[100],to[100],c[100][100],s[100][100];
inline void push(int v){
    if(p[v]<0)return;
    c[p[v]][v]--;
    c[v][p[v]]++;
    s[v][p[v]]*=-1;
    s[p[v]][v]*=-1;
    push(p[v]);
}
inline int path(){
int i,j,k;
    for(i=0;i<n;i++){
        if(c[0][i]){
            to[i]=s[0][i];
            p[i]=0;
        }
        else p[i]=i;
    }
    to[0]=0;
    p[0]=-1;
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            if(p[i]!=i)
                for(j=0;j<n;j++)
                    if(c[i][j] && (p[j]==j || s[i][j]+to[i]<to[j])){
                        p[j]=i;
                        to[j]=s[i][j]+to[i];
                    }
    if(p[n-1]==n-1)return 0;
    push(n-1);
    return to[n-1];
}
main(){
int i,j,k,m;
long long num,cap,sum;
while(scanf("%d %d",&n,&m)!=EOF){
    for(sum=i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=c[j][i]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        c[i][j]=c[j][i]=1;
        s[i][j]=s[j][i]=k;
    }
    scanf("%lld %lld",&num,&cap);
    while(num>0){
        k=path();
        if(!k)break;
        sum+=k*(num<?cap);
        num-=cap;
    }
    if(num>0)puts("Impossible.");
    else printf("%lld\n",sum);
}
}
