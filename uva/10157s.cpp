#define Size 11
#define Default 0
#include"bigint0.h"
#define MAX 150
bigint s[MAX+1][MAX+1],sum;
main(){
int i,j,k,p1,p2;
char line[100];
for(i=0;i<=MAX;i++){
    s[i][0]=1;
    s[i][1]=1;
}
    //s[i][j] = (s[k][j-1]*s[i-k-1][j], 0<=k<=i-1)
for(i=2;i<=MAX;i++){
    for(j=2;j<i;j++){
        for(k=0;k<=i-1;k++){
            p1=k<?j-1;p2=i-k-1<?j;
            if(k==0)s[i][j]+=s[i-k-1][p2];
			else if(i-k-1==0)s[i][j]+=s[k][p1];
			else if(s[k][p1].num[0]==0 && s[k][p1].d==0)
                s[i][j]+=s[i-k-1][p2];
			else if(s[i-k-1][p2].num[0]==1 && s[i-k-1][p2].d==0)
                s[i][j]+=s[k][p1];
            else s[i][j]+=(s[k][p1]*s[i-k-1][p2]);
        }
    }
    s[i][i]=s[i][i-1];
    s[i][i].num[0]+=1;
    s[i][i].carry();
}
while(scanf("%d %d",&i,&j)!=EOF){
    if(i%2==1){puts("0");continue;}
    if(j>i/2){puts("0");continue;}
    sum=s[i/2][j];
    if(j-1>=1)sum-=s[i/2][j-1];
    sum.show();
}
}
