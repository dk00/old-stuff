#include<stdio.h>
int row[8],col[8],rc[15],cr[15],point[8][8],max,sum;
void dfs(int c){
    if(c>=8){
        for(c=0,sum=0;c<8;c++)
            sum+=point[col[c]][c];
        max=sum>max?sum:max;
        return;
    }
    int r=0;
    for(;r<8;r++){
        for(;r<8 && (row[r]+rc[7+r-c]+cr[r+c])<3;r++);
        if(r>=8)break;
        rc[7+r-c]=0;cr[r+c]=0;
        row[r]=0;col[c]=r;
        dfs(c+1);
        rc[7+r-c]=1;cr[r+c]=1;
        row[r]=1;col[c]=-1;
    }
}
main(){
int i,j,n;
scanf("%d",&n);
for(;n>0;n--){
    for(i=0;i<8;i++){
        row[i]=1;col[i]=-1;rc[i]=1;cr[i]=1;
    }
    for(;i<15;i++){
        rc[i]=1;cr[i]=1;
    }
    for(i=0;i<8;i++){
        for(j=0;j<8;j++)
            scanf("%d",&point[i][j]);
    }
    max=0;
    dfs(0);
    printf("%5d\n",max);
}
}
