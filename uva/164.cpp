#include<stdio.h>
enum {I,D,C,N};
int pos,dp[21][21],pv[21][21];
char s1[220],s2[220];
void trace(int i,int j){
    if(i || j){
        if(pv[i][j]==I){
            trace(i,j-1);
            printf("I%c%02d",s2[j],pos++);
        }
        if(pv[i][j]==D){
            trace(i-1,j);
            printf("D%c%02d",s1[i],pos);
        }
        if(pv[i][j]==C){
            trace(i-1,j-1);
            printf("C%c%02d",s2[j],pos++);
        }
        if(pv[i][j]==N)
            trace(i-1,j-1),pos++;
    }
    else pos=1;
}
main(){
int i,j,k;
while(scanf("%s %s",s1+1,s2+1)==2){
    for(i=1;s1[i];i++)dp[i][0]=i,pv[i][0]=D;
    for(j=1;s2[j];j++)dp[0][j]=j,pv[0][j]=I;
    for(i=1;s1[i];i++)
        for(j=1;s2[j];j++)
            if(s1[i]==s2[j])
                dp[i][j]=dp[i-1][j-1],pv[i][j]=N;
            else if(dp[i-1][j]<dp[i][j-1] && dp[i-1][j]<dp[i-1][j-1])
                dp[i][j]=dp[i-1][j]+1,pv[i][j]=D;
            else if(dp[i][j-1]<dp[i-1][j] && dp[i][j-1]<dp[i-1][j-1])
                dp[i][j]=dp[i][j-1]+1,pv[i][j]=I;
            else dp[i][j]=dp[i-1][j-1]+1,pv[i][j]=C;
    trace(i-1,j-1);
    puts("E");
}
}
