#include<stdio.h>
int s[51][51],path[51][51],step,n,
mx[8]={1,2,1,2,-1,-2,-1,-2},my[8]={2,1,-2,-1,2,1,-2,-1},min;
int dfs(int x,int y){
    if(s[x][y]>=9)return 1;
    path[x][y]=step++;s[x][y]=5000;
    if(step>n*n)return 0;
    int i;
    for(i=0;i<8;i++){
        if(x+mx[i]<n && x+mx[i]>=0 && y+my[i]<n && y+my[i]>=0)
            break;
    }
    if(i>=8) return 1;
    min=i;
    s[x+mx[min]][y+my[min]]--;
    for(i++;i<8;i++){
        if(x+mx[i]<n && x+mx[i]>=0 && y+my[i]<n && y+my[i]>=0){
            s[x+mx[i]][y+my[i]]--;
            if(s[x+mx[min]][y+my[min]]>s[x+mx[i]][y+my[i]])
                min=i;
        }
    }
    return dfs(x+mx[min],y+my[min]);
}
main(){
int i,j,k,x,y,first=1;
while(scanf("%d %d %d",&n,&x,&y)!=EOF){
    if(first)first=0;
    else puts("");
    if(n==1){
        printf("    1\n");
        continue;
    }
    for(step=1,i=2;i<n-2;i++){
        for(j=2;j<n-2;j++){
            s[i][j]=8;
        }
        s[i][0]=s[0][i]=s[n-1][i]=s[i][n-1]=4;
        s[i][1]=s[1][i]=s[n-2][i]=s[i][n-2]=6;
    }
    s[0][0]=s[0][n-1]=s[n-1][0]=s[n-1][n-1]=2;
    s[0][1]=s[1][0]=s[n-2][0]=s[0][n-2]=s[1][n-1]=s[n-1][1]=
    s[n-1][n-2]=s[n-2][n-1]=3;
    s[1][1]=s[1][n-2]=s[n-2][1]=s[n-2][n-2]=4;
    if(n<=5 || n%2==1)printf("No Circuit Tour.\n");
    else{
        dfs(x,y);
        for(i=0;i<n;i++){
            for(j=0;j<n;j++)
                printf("%5d",path[i][j]);
            puts("");
        }
    }
}
}
