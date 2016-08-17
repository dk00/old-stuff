#include<stdio.h>
#include<stdlib.h>
int v[1000],p[1000],to[1000],num[1000],c[1000][1000];
int discmp(const void *a,const void *b){
    return to[*(int *)b]-to[*(int *)a];
}
main(){
int i,j,k,n,m;
while(scanf("%d %d",&n,&m) && n){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        c[i][j]=c[j][i]=k;
    }
    for(i=0;i<n;i++){
        to[i]=c[1][i];
        if(!to[i])to[i]=2000000000;
        p[i]=1;
    }
    to[1]=0;
    while(1){
        for(i=0;i<n && p[i]==i;i++);
        if(i>=n)break;
        for(j=i+1;j<n;j++)
            if(p[j]!=j && to[j]<to[i])i=j;
        if(to[j]>=2000000000)break;
        p[i]=i;
        for(j=0;j<n;j++)
            if(c[i][j])
                to[j]<?=(to[i]+c[i][j]);
    }
    for(i=0;i<n;i++)v[i]=i;
    qsort(v,n,sizeof(v[0]),discmp);
    for(i=0;i<n;i++)
        p[i]=i,num[i]=0;
    num[0]=1;
    for(i=0;v[i];i++);
    for(;i<n;i++)
        for(j=i+1;j<n;j++)
            if(c[v[i]][v[j]])
                num[v[j]]+=num[v[i]];
    printf("%d\n",num[v[n-1]]);
}
}
