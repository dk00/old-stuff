#include<stdio.h>
long long time;
int n,o[100][100],r[100][100],c[100][100],t[100][100];
void flow(int D){
    time=0;
int i,j,k=0,p[100],to[100];
    while(D-=k){
        to[0]=0;
        p[0]=-1;
        for(i=1;i<n;i++){
            if(c[0][i]>0){
                p[i]=0;
                to[i]=t[0][i];
            }
            else p[i]=i;
        }
        for(k=0;k<n;k++)
        for(i=0;i<n;i++){
            if(p[i]==i)continue;
                for(j=1;j<n;j++)
                    if(c[i][j]>0 && (p[j]==j || (c[i][j]>o[i][j]?
                    to[i]-t[i][j]:to[i]+t[i][j])<to[j])){
                        to[j]=(c[i][j]>o[i][j]?to[i]-t[i][j]:to[i]+t[i][j]);
                        p[j]=i;
                    }
        }
        for(i=n-1,k=c[p[i]][i]<?D;p[i]>=0;i=p[i])
            k<?=(c[p[i]][i]>o[p[i]][i]?c[p[i]][i]-o[p[i]][i]:c[p[i]][i]);
        for(i=n-1;p[i]>=0;i=p[i]){
            time+=k*t[p[i]][i];
            c[p[i]][i]-=k;
            c[i][p[i]]+=k;
        }
    }
}
int flow1(){
int i,j,k,sum=0,p[100],q[1000];
    while(1){
        q[0]=0;
        p[0]=-1;
        for(i=1;i<n;i++)
            p[i]=i;
        for(i=0,j=1;i<j;i++){
            if(p[n-1]-n+1)break;
            for(k=1;k<n;k++)
                if(c[q[i]][k]>0 && p[k]==k){
                    q[j++]=k;
                    p[k]=q[i];
                }
        }
        if(p[n-1]==n-1)break;
        for(k=c[p[n-1]][n-1],j=n-1;p[j]>=0;j=p[j])
            k<?=c[p[j]][j];
        for(j=n-1;p[j]>=0;j=p[j]){
            c[p[j]][j]-=k;
            c[j][p[j]]+=k;
        }
        sum+=k;
    }
    return sum;
}
main(){
int i,j,k,f,m,D;
while(scanf("%d %d",&n,&m)!=EOF){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            o[i][j]=c[i][j]=t[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        t[i][j]=t[j][i]=k;
        o[i][j]=o[j][i]=1;
    }
    scanf("%d %d",&D,&k);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(o[i][j])
                o[i][j]=c[i][j]=k;
    f=flow1();
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=o[i][j];
    if(f<D){
        puts("Impossible.");
        continue;
    }
    flow(D);
    printf("%lld\n",time);
}
}
