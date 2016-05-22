#include<stdio.h>
#include<stdlib.h>
const char lr[]={" LR"};
int n,num[50][25],p[50][25][501],path[500];
long long sum,s1[50][25][501];
/*void go_u(int h,int c,int s){
    if(h>n-2){
        return;
    }
    else{
        if(p[h][c][s]&1)go(h+1,c-1,s-num[h][c]);
        if(p[h][c][s]&2)go(h+1,c,s-num[h][c]);
    }
void go_d(int h,int c,int s){
    if(s==num[h][c]){
        return;
    }
    if(p[h][c][s]&1)go(h+1,c-1,s-num[h][c]);
    if(p[h][c][s]&2)go(h+1,c,s-num[h][c]);
}*/
int find(int h,int c,int s){
    if(h==(n*2-2))
        return 1;
    if(h>n-2){
        if(p[h][c][s]&1){
            path[h]=1;
            if(find(h+1,c,s-num[h][c]))return 1;
        }
        else if(p[h][c][s]&2){
            path[h]=2;
            if(find(h+1,c+1,s-num[h][c]))return 1;
        }
    }
    else{
        if(p[h][c][s]&1){
            path[h]=1;
            if(find(h+1,c-1,s-num[h][c]))return 1;
        }
        if(p[h][c][s]&2){
            path[h]=2;
            if(find(h+1,c,s-num[h][c]))return 1;
        }
    }
    return 0;
}
void show(int h,int c){
    if(h>n*2-3)return;
    if(path[h]==1){
        putchar('L');
        if(h>n-2)show(h+1,c-1);
        else show(h+1,c);
    }
    else if(path[h]==2){
        putchar('R');
        if(h>n-2)show(h+1,c);
        else show(h+1,c+1);
    }
}
main(){
int i,j,k,s;
while(scanf("%d %d",&n,&s) && n+s){
    for(i=0;i<n;i++)
        for(j=0;j<n-i;j++)
            scanf("%d",&num[i][j]);
    for(i=1;i<n;i++)
        for(j=0;j<=i;j++)
            scanf("%d",&num[i+n-1][j]);
    if(s>(n*2-1)*9){
        puts("0\n");
        continue;
    }
    for(i=0;i<n;i++)
        for(j=0;j<n-i;j++)
            for(k=0;k<=s;k++){
                s1[i][j][k]=0;
                p[i][j][k]=0;
            }
    for(i=1;i<n;i++)
        for(j=0;j<=i;j++)
            for(k=0;k<=s;k++){
                s1[i+n-1][j][k]=0;
                p[i+n-1][j][k]=0;
            }
    for(j=0;j<n;j++){
        p[n*2-2][j][num[n*2-2][j]]=-1;
        s1[n*2-2][j][num[n*2-2][j]]=1;
    }
    for(i=n-2;i>=0;i--)
        for(j=0;j<=i;j++)
            for(k=s-num[i+n-1][j];k>=0;k--){
                if(p[i+n][j+1][k]){
                    p[i+n-1][j][k+num[i+n-1][j]]|=2;
                    s1[i+n-1][j][k+num[i+n-1][j]]+=s1[i+n][j+1][k];
                }
                if(p[i+n][j][k]){
                    p[i+n-1][j][k+num[i+n-1][j]]|=1;
                    s1[i+n-1][j][k+num[i+n-1][j]]+=s1[i+n][j][k];
                }
            }
    for(i=n-2;i>=0;i--){
        for(k=s-num[i][0];k>=0;k--)
            if(p[i+1][0][k]){
                p[i][0][k+num[i][0]]|=2;
                s1[i][0][k+num[i][0]]+=s1[i+1][0][k];
            }
        for(j=1;j<n-i-1;j++)
            for(k=s-num[i][j];k>=0;k--){
                if(p[i+1][j][k]){
                    p[i][j][k+num[i][j]]|=2;
                    s1[i][j][k+num[i][j]]+=s1[i+1][j][k];
                }
                if(p[i+1][j-1][k]){
                    p[i][j][k+num[i][j]]|=1;
                    s1[i][j][k+num[i][j]]+=s1[i+1][j-1][k];
                }
            }
        for(k=s-num[i][n-i-1];k>=0;k--)
            if(p[i+1][n-i-2][k]){
                p[i][n-i-1][k+num[i][n-i-1]]|=1;
                s1[i][n-i-1][k+num[i][n-i-1]]+=s1[i+1][n-i-2][k];
            }
    }
    for(sum=j=0;j<n;j++)
        sum+=s1[0][j][s];
    printf("%lld\n",sum);
    if(!sum){
        puts("");
        continue;
    }
    for(j=0;j<n;j++)
        if(p[0][j][s]){
            if(find(0,j,s)){
                printf("%d ",j);
                show(0,j);
                break;
            }
        }
    puts("");
}
}
