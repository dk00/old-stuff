#include<stdio.h>
#define SIZE 110
#define Err 1e-9
char Map[SIZE][SIZE];
int c[SIZE][SIZE],t;
double dp[SIZE][10010];
main(){
    int T,C,i,j,k,n,R,x,y,z;
    scanf("%d",&T);
    while(T--){
        t++;
        scanf("%d %d",&n,&R);
        for(i=0;i<=n;i++)
            for(j=0;j<=10000;j++)dp[i][j]=0;
        dp[0][0]=1;
        for(i=1;i<=n;i++)
            for(j=i-1;j<=(i-1)*R;j++)
                for(k=1;k<=R;k++)dp[i][j+k]+=dp[i-1][j]/R;
        for(i=0;i<=n;i++)
            for(j=1;j<=10000;j++)dp[i][j]+=dp[i][j-1];
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)c[i][j]=-1;
        for(i=0;i<n;i++)scanf("%s",Map[i]);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(Map[i][j]=='Y')c[i][j]=1;
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                if(c[i][k]!=-1)
                    for(j=0;j<n;j++)
                        if(c[k][j]!=-1)
                            if(c[i][j]==-1||c[i][j]>c[i][k]+c[k][j])
                                c[i][j]=c[i][k]+c[k][j];
        scanf("%d",&C);
        printf("Case %d\n",t);
        while(C--){
            scanf("%d %d %d",&x,&y,&z);
            if(c[x-1][y-1]<0)puts("0.000");
            else printf("%.3lf\n",dp[c[x-1][y-1]][z]+Err);
        }
        puts("");
    }
}
