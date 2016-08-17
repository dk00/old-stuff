#include<stdio.h>
long long time,p[100],to[100];
int n,o[100][100],c[100][100],t[100][100];
void flow(int d){
int i,j,k=0;
    while(d-=k){
        p[0]=-1;
        to[0]=0;
        for(i=1;i<n;i++){
            if(c[0][i]){
                p[i]=0;
                to[i]=c[0][i];
            }
            else p[i]=i;
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++){
                if(p[i]==i)continue;
                for(j=0;j<n;j++){
                    if(p[j]==j && c[i][j]>0){
                        if(c[i][j]<=o[i][j])
                            to[j]=to[i]+t[i][j];
                        else
                            to[j]=to[i]-t[i][j];
                        p[j]=i;
                    }
                    else if(c[i][j]>0){
                        if(c[i][j]<=o[i][j]){
                            if(to[i]+t[i][j]<to[j]){
                                to[j]=to[i]+t[i][j];
                                p[j]=i;
                            }
                        }
                        else if(to[i]-t[i][j]<to[j]){
                            to[j]=to[i]-t[i][j];
                            p[j]=i;
                        }
                    }
                }
            }
        k=c[p[n-1]][n-1];
        if(k>o[p[n-1]][n-1])k-=o[p[n-1]][n-1];
        k<?=d;
        for(i=n-1;p[i]>=0;i=p[i]){
            if(c[p[i]][i]>o[p[i]][i])
                k<?=(c[p[i]][i]-o[p[i]][i]);
            else
                k<?=c[p[i]][i];
        }
        for(i=n-1;p[i]>=0;i=p[i]){
            if(c[p[i]][i]>o[p[i]][i])
                time-=t[p[i]][i]*k;
            else
                time+=t[p[i]][i]*k;
            c[p[i]][i]-=k;
            c[i][p[i]]+=k;
        }
    }
}
int flow1(){
int i,j,k,sum=0,q[1000];
    while(1){
        p[0]=-1;
        q[0]=0;
        for(i=1;i<n;i++)p[i]=i;
        for(i=0,j=1;i<j;i++){
            if(p[n-1]-n+1)break;
            for(k=0;k<n;k++)
                if(c[q[i]][k] && p[k]==k){
                    p[k]=q[i];
                    q[j++]=k;
                }
        }
        if(p[n-1]==n-1)break;
        for(j=n-1,k=c[p[n-1]][n-1];p[j]>=0;j=p[j])
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
int i,j,k,d,m;
while(scanf("%d %d",&n,&m)!=EOF){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=t[i][j]=0;
    while(m--){
        scanf("%d %d %d",&i,&j,&k);
        i--,j--;
        t[i][j]=t[j][i]=k;
        c[i][j]=c[j][i]=1;
    }
    scanf("%d %d",&d,&k);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(c[i][j])
                o[i][j]=c[i][j]=k;
    k=flow1();
    if(k<d){
        puts("Impossible.");
        continue;
    }
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=o[i][j];
    time=0;
    flow(d);
    printf("%lld\n",time);
}
}
