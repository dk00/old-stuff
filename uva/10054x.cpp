#include<stdio.h>
int c[50][50],v[50],test[50];
void inline vis(int p){
    if(test[p])return;
    test[p]=1;
    for(int i=0;i<50;i++)
        if(c[p][i])
            vis(i);
}
void inline go(int p){
    int i;
    if(!v[p])return;
    for(i=0;i<50 && v[p];i++)
        if(c[p][i]){
            c[p][i]--,c[i][p]--;
            v[i]--,v[p]--;
            go(i);
            printf("%d %d\n",i+1,p+1);
        }
}
main(){
int i,j,n,t,C=0;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<50;i++)
        for(j=v[i]=test[i]=0;j<50;j++)
            c[i][j]=0;
    while(n--){
        scanf("%d %d",&i,&j);
        i--,j--;
        v[i]++,v[j]++;
        c[i][j]++,c[j][i]++;
    }
    for(i=0;!v[i];i++);
    vis(i);
    for(i=0;i<50;i++)
        if(v[i] && !test[i])break;
    if(i<50){
        puts("some beads may be lost");
        continue;
    }
    for(i=j=0;i<50;i++)
        j+=(v[i]&1);
    if(j){
        puts("some beads may be lost");
        continue;
    }
    for(i=0;i<50;i++)
        if(v[i] && v[i]&1)break;
    if(C++)puts("");
    printf("Case #%d\n",C);
    if(i<50){
        go(i);
        continue;
    }
    for(i=0;v[i]==0;i++);
    go(i);
}
}
