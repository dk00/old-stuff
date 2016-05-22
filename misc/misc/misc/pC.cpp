#include<stdio.h>
#include<string.h>
int Three[15],cover[9][9],result[5000000];
char Map[9][9];
struct data{
    int a[4][4];
    void fill(char b[][9]){
        int i,j;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++){
                if(b[i][j]=='.')a[i][j]=0;
                else if(b[i][j]=='x')a[i][j]=1;
                else a[i][j]=2;
            }
    }
};
int Check(data &X,int player){
    int i,j;
    for(i=0;i<4;i++){
        for(j=0;j<4;j++)
            if(X.a[i][j]!=player)break;
        if(j==4)return 1;
        for(j=0;j<4;j++)
            if(X.a[j][i]!=player)break;
        if(j==4)return 1;
    }
    for(i=0;i<4;i++)
        if(X.a[i][i]!=player)break;
    if(i==4)return 1;
    for(i=0;i<4;i++)
        if(X.a[i][3-i]!=player)break;
    if(i==4)return 1;
    return 0;
}
int Q(data &X,int player,int state){
    if(result[state]!=0)return result[state];
    if(Check(X,3-player)){
        result[state]=3-player;
        return result[state];
    }
    int i,j,k;
    bool flag=1;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            if(X.a[i][j]==0){
                X.a[i][j]=player;
                k=Q(X,3-player,state+Three[cover[i][j]]*player);
                if(k==player){
                    result[state]=player;
                    X.a[i][j]=0;
                    return player;
                }
                if(k!=3-player)flag=0;
                X.a[i][j]=0;
            }
    if(flag){
        result[state]=3-player;
        return result[state];
    }
    result[state]=3;
    return 3;
}
main(){
    int T,i,j,k;
    char s[99];
    Three[0]=1;
    for(i=1;i<=14;i++)Three[i]=Three[i-1]*3;
    data now;
    scanf("%d",&T);
    while(T--){
        memset(result,0,sizeof(result));
        scanf("%s",s);
        for(i=0;i<4;i++)scanf("%s",Map[i]);
        k=0;
        for(i=0;i<4;i++)
            for(j=0;j<4;j++){
                if(Map[i][j]=='.')cover[i][j]=k++;
                else cover[i][j]=-1;
            }
        now.fill(Map);
        if(Q(now,1,0)==1)printf("YES\n");
        else printf("NO\n");
    }
}
