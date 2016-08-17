#define Size 200
#define Default 0
#include"bigint0.h"
#define MAX 50
#define min(a,b) (a)<(b)?(a):(b)
bigint s[MAX+1][MAX+1];
main(){
int i,j,k,p1,p2;
for(i=0;i<=MAX;i++){
    s[i][0]=1;
    s[i][1]=1;
}
    //s[i][j] = (s[k][j-1]*s[i-k-1][j], 0<=k<=i-1)
for(i=3;i<=MAX;i++){
    printf("%d ",i);
    for(j=2;j<=i-1;j++){
        for(k=0;k<=i-1;k++){
            p1=min(k-1,j-1);p2=min(i-k-2,j);
            if(k==0)s[i][j]+=s[i-k-1][p2];
			else if(i-k-1==0)s[i][j]+=s[k][p1];
            else s[i][j]+=(s[k][p1]*s[i-k-1][p2]);
        }
    }
//    s[i][i-1]=s[i][i-2];
//    s[i][i-1].num[0]+=1;
//    s[i][i-1].carry();
}
while(scanf("%d %d",&i,&j)!=EOF){
    puts(s[i][j].tostr());
}
}
