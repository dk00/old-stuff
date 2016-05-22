#include<stdio.h>
#define MAXD 10
#define MAX 150
//87
/*s[i][j] = (s[k][j-1]*s[i-k][j], 0<=k<=i-1)
s[0][j-1]*s[i-1][j] + s[1][j-1]*s[i-2][j] ... s[i-1][j-1]*s[0][j]
s[4][2] =
s[0][1]*s[3][2] + s[1][1]*s[2][2] + s[2][1]*s[1][2] + s[3][1]*s[0][2]
        ^^^^^^^   ^^^^^^^^^^^^^^^   ^^^^^^^           ^^^^^^^
k>=j-1, k<=i-j
*/
long long s[MAX+1][MAX+1][MAXD+1],tmp[MAXD+1],R=100000;
long d[MAX+1][MAX+1],td;
main(){
long i,j,k,p,q,m1,m2;R*=R/10;
for(i=0;i<=MAX;i++){
    s[0][i]=s[i][1]=1;
    d[0][i]=d[i][1]=MAXD;
}
s[2][2][d[2][2]=MAXD]=2;
s[3][2][d[3][2]=MAXD]=4;s[3][3][d[3][3]=MAXD]=5;
for(i=4;i<=MAX;i++){                    //n
    for(j=2;j<=i;j++){                  //d
        s[i][j][d[i][j]=MAXD]=0;
        for(k=1;k<=i-1;k++){
    //s[i][j] = (s[k][j-1]*s[i-k][j], 0<=k<=i-1)
            m1=k<?j-1;m2=i-k<?j;
            for(p=d[m1][j-1]+d[m2][j]-10>?0;p<=MAXD;p++)tmp[p]=0;
            for(p=MAXD;p>=d[m1][j-1];p--){
                for(q=MAXD;q>=d[m2][
            }
            for(p=MAXD;p1>d[i][j];p--){  //carry
                if(s[i][j][p]>=R){
                    s[i][j][p-1]+=s[i][j][p]/R;
                    s[i][j][p]%=R;
                }
            }
            if(s[i][j][d[i][j]]>=R){
                s[i][j][d[i][j]-1]=s[i][j][d[i][j]]/R;
                s[i][j][d[i][j]--]%=R;
            }
        }
    }
}
while(scanf("%ld %ld",&n,&d)!=EOF){
    if(n%2==1){puts("0");continue;}
    n/=2;
    printf("%lld",s[n][d][s[n][d]]);
    for(p=d[n][d]+1;p<=MAXD;p++)
        printf("%09lld",s[n][d][p]);
    puts("");
}
}
