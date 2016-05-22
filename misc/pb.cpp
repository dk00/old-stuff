#include<stdio.h>
struct dp
{
    int used;
    int tused;
};
dp DP[5][2000000];
main(){
    freopen("pb.in","r",stdin);
    freopen("pb.out","w",stdout);
    int noc[5],c[5]={1,5,10,20,50};
    int i,j,n,pay,temp,sum;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&pay);
        for(i=0;i<5;i++)
            scanf("%d",&noc[i]);
        for(i=0;i<5;i++){
            scanf("%d",&temp);
            noc[i]+=temp;
            pay+=temp*c[i];
        }
        sum=0;
        for(i=0;i<5;i++)
            sum+=noc[i];
        for(j=0;j<=pay;j++)
            DP[0][j].used=-1;
        for(j=0;j<=noc[0];j++){
            DP[0][j].used=0;
            DP[0][j].tused=j;
        }
        for(i=1;i<=4;i++){
            for(j=0;j<=pay;j++){
                if(DP[i-1][j].used>=0){
                    DP[i][j].used=0;
                    DP[i][j].tused=DP[i-1][j].tused;
                }
                else if(j>=c[i] && DP[i][j-c[i]].used>=0 && DP[i][j-c[i]].used<noc[i]){
                    DP[i][j].used=DP[i][j-c[i]].used+1;
                    DP[i][j].tused=DP[i][j-c[i]].tused+1;
                }
                else
                    DP[i][j].used=-1;
            }
        }
        printf("%d\n",sum-DP[4][pay].tused);
    }
}
