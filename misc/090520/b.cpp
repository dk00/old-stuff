#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
int area(int x[],int y[])
{
    x[3]=x[0],y[3]=y[0];
    int sum=0;
    for(int i=0;i<3;i++)
        sum+=x[i]*y[i+1]-y[i]*x[i+1];
    return abs(sum);
}
int IN(int px,int py,int x[],int y[])
{
    int sum=area(x,y);
    for(int i=0;i<3;i++){
        swap(px,x[i]);
        swap(py,y[i]);
        sum-=area(x,y);
        swap(px,x[i]);
        swap(py,y[i]);
    }
    return !sum;
}
char type[1001][9];
int x[1001][4],y[1001][4];
main()
{
    int i,j,k,T,n,px,py,C=1;
    freopen("pb.in","r",stdin);
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        printf("case %d:\n",C++);
        for(i=0;i<n;i++){
            scanf("%s",type[i]);
            if(!strcmp(type[i],"ask")){
                scanf("%d %d",&px,&py);
                for(j=k=0;j<i;j++){
                    if(strcmp(type[j],"ask") &&
                    IN(px,py,x[j],y[j])){
                        if(!strcmp(type[j],"cut"))
                            k=0;
                        else k++;
                    }
                }
                printf("%d\n",k);
            }
            else
                for(j=0;j<3;j++)
                    scanf("%d %d",&x[i][j],&y[i][j]);
        }
    }
}
