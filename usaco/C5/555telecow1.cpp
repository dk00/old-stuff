/*
ID: s0000151
PROG: telecow
LANG: C++
*/
#include<stdio.h>
int n,s,t,path[200],use[200],c[200][200],f[200][200];
int go(int p){
    if(p==t)return 1;
    if(!use[p])return 0;
    use[p]=0;
    for(int i=0;i<n;i++)
        if(f[p][i]){
            f[p][i]--;
            if(go(i)){
                f[i][p]++;
                return 1;
            }
            f[p][i]++;
        }
    return 0;
}
int flow(){
int i,j,fo=0;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)f[i][j]=c[i][j];
    use[s]=1;
    for(i=0;i<n;i++)use[i]=1;
    while(go(s)){
        fo++;
        for(i=0;i<n;i++)use[i]=1;
    }
    return fo;
}
main(){
freopen("telecow.in","r",stdin);
freopen("telecow.out","w",stdout);
int i,j,m,f1,f2,la=10000;
scanf("%d %d %d %d",&n,&m,&s,&t);
s--,t--;
for(i=0;i<n;i++)
    c[i][i+n]=c[i+n][i]=1;
while(m--){
    scanf("%d %d",&i,&j);
    i--,j--;
    c[i+n][j]=la;
    c[j+n][i]=la;
}
c[s][s+n]=c[t][t+n]=la,t+=n,m=n,n<<=1;
printf("%d\n",f1=flow());
for(i=0;f1 && i<m;i++){
    if(i==s || i==t-m)continue;
    c[i][i+m]=c[i+m][i]=0;
    f2=flow();
    if(f2<f1)printf("%d%c",i+1,(f1=f2)?' ':'\n');
    else c[i][i+n]=c[i+n][i]=1;
}
}
