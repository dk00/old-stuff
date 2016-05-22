#include<cstdio>
using namespace std;
const int N=1300;
int flow[N][N];
int capa[N][N];
int w[N][N],u[N];
int en;
int ans;
int que[N*N],qb,qe;

void do_flow(){
    int dis[N]={0};
    int last[N];
    int i;
    for(i=0;i<=2*en+1;i++){
        u[i]=1;
        last[i]=-1;
        dis[i]=-99999999;
    }
    que[0]=0;
    qb=0;
    qe=1;
    dis[0]=0;
    while(qb<qe){
        int n=que[qb];
        u[n]=1;
        for(i=0;i<=2*en+1;i++){
            if(flow[n][i]<capa[n][i]){
                //printf("%d %d -> %d\n",n,i,w[n][i]);
                if(dis[n]+w[n][i]>dis[i]){
                    dis[i]=dis[n]+w[n][i];
                    last[i]=n;
                    if(i!=2*en+1){
                        if(u[i])
                            u[i]=0,que[qe++]=i;
                    }
                }
            }
        }
        qb++;
    }
    if(last[2*en+1]!=-1){
        for(i=2*en+1;i!=0;i=last[i]){
            int l=last[i];
            ans+=w[l][i];
            flow[l][i]++;
            flow[i][l]--;
            //printf("<%d, %d>", l, i);
        }
    }
//    printf("\n");
}

int main(){
    int ecase;
    int i,j;
    freopen("pc.in","r",stdin);

    scanf("%d",&ecase);
    while(ecase>0){
        scanf("%d",&en);
        for(i=0;i<2*en+2;i++)
            for(j=0;j<2*en+2;j++){
                flow[i][j]=0;
                capa[i][j]=0;
                w[i][j]=0;
            }
        for(i=1;i<=en;i++){
            capa[0][i]=1;
    //        w[i][j]=1;
        }
        for(i=en+1;i<=2*en;i++){
            capa[i][2*en+1]=1;
      //      w[i][j]=1;
        }
        for(i=0;i<en;i++)
            for(j=0;j<en;j++){
                int t1,t2,tc;
                scanf("%d%d%d",&t1,&t2,&tc);
                if(en+1<=t1 && t1<=2*en)
                    t1^=t2^=t1^=t2;
                capa[t1][t2]=1;
                w[t1][t2]=tc;
                w[t2][t1]=-tc;
            }
        ans=0;
        for(i=0;i<en;i++){
            do_flow();
            //printf("---\n");
        }
        printf("%d\n",ans);

        int signal;
        scanf("%d",&signal);
        ecase--;
    }
    return 0;
}
