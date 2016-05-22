#include<stdio.h>
int n,m,u,map[76][75],r[7][75][75],walk[7][75][75];
void next(int neg,int i,int j,int sum){
    if(i<n-1 && map[i+1][j]<0)neg++;
    if(neg>m || ++i>=n)return;
    if(r[neg][i][j]-u){
        r[neg][i][j]=u;
        walk[neg][i][j]=sum;
    }
    walk[neg][i][j]>?=sum;
}
main(){
int i,j,k,l,sum,max,neg,C=1;
while(scanf("%d %d",&n,&m) && n+m){
    for(i=0,u++;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&map[i][j]);
    if(n==1){
        printf("Case %d: %d\n",**map,C++);
        continue;
    }
    for(i=sum=neg=0;i<n && neg<=m;i++){
        sum+=map[0][i];
        if(map[0][i]<0)neg++;
        next(neg,0,i,sum);
    }
    for(i=1;i<n;i++)
        for(j=0;j<n;j++)
            for(l=0;l<=m;l++){
                if(r[l][i][j]-u)continue;
                for(k=j,sum=walk[l][i][j],neg=l;k>=0;k--){
                    sum+=map[i][k];
                    if(map[i][k]<0)neg++;
                    if(neg>m)break;
                    next(neg,i,k,sum);
                }
                for(k=j,sum=walk[l][i][j],neg=l;k<n;k++){
                    sum+=map[i][k];
                    if(map[i][k]<0)neg++;
                    if(neg>m)break;
                    next(neg,i,k,sum);
                }
            }
    for(i=sum=0,j=n-1,max=2147483647+1;i<=m;i++){
        if(r[i][j][j]-u)continue;
        walk[i][j][j]+=map[j][j];
        max>?=walk[i][j][j];
        sum=1;
    }
    if(sum)printf("Case %d: %d\n",C++,max);
    else printf("Case %d: impossible\n",C++);
}
}
