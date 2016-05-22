#include<stdio.h>
const int len=9;
main(){
    int s[len+5],way[2][50][10],i,j,black=0,white=0;
while(scanf("%d",&s[0])==1){
    black=white=0;
/*    for(i=0;i<50;i++)
        for(j=0;j<10;j++)
            way[0][i][j]=0;*/
    for(i=1;i<len;i++)
        scanf("%d",&s[i]);
    for(i=0;i<len-2;i++){   //black
        if(s[i]==1){
            if(i>0 && s[i-1]==0){
                if(s[i+1]==1){
                    if(s[i+2]==1 && s[i+3]==0 && s[i+4]==0){    //0 1 1 1 0 0
                        way[0][black][0]=2;
                        way[0][black][1]=i-1;
                        way[0][black][2]=i+3;
                        black++;
                        continue;
                    }
                    if(s[i+2]==0 && s[i+3]==1 && s[i+4]==0){    //0 1 1 0 1 0
                        way[0][black][0]=3;
                        way[0][black][1]=i-1;
                        way[0][black][2]=i+2;
                        way[0][black][3]=i+4;
                        black++;
                        continue;
                    }
                }
                if(s[i+1]==0){
                    if(s[i+2]==1 && s[i+3]==1 && s[i+4]==0){    //0 1 0 1 1 0
                        way[0][black][0]=3;
                        way[0][black][1]=i-1;
                        way[0][black][2]=i+1;
                        way[0][black][3]=i+4;
                        black++;
                        continue;
                    }
                }
                if(s[i+1]==0 && s[i+2]==1 && s[i+3]==1 && s[i+4]==1){
                    way[0][black][0]=1;
                    way[0][black][1]=i+1;
                    black++;
                    continue;
                }
                if(s[i+1]==1 && s[i+2]==0 && s[i+3]==1 && s[i+4]==1){
                    way[0][black][0]=1;
                    way[0][black][1]=i+2;
                    black++;
                    continue;
                }
                if(s[i+1]==1 && s[i+2]==1 && s[i+3]==0 && s[i+4]==1){
                    way[0][black][0]=1;
                    way[0][black][1]=i+3;
                    black++;
                    continue;
                }
            }
            if(i==0 || s[i-1]==2){
                if(s[i+1]==0 && s[i+2]==1 && s[i+3]==1 && s[i+4]==1){
                    way[0][black][0]=1;
                    way[0][black][1]=i+1;
                    black++;
                    continue;
                }
                if(s[i+1]==1 && s[i+2]==0 && s[i+3]==1 && s[i+4]==1){
                    way[0][black][0]=1;
                    way[0][black][1]=i+2;
                    black++;
                    continue;
                }
                if(s[i+1]==1 && s[i+2]==1 && s[i+3]==0 && s[i+4]==1){
                    way[0][black][0]=1;
                    way[0][black][1]=i+3;
                    black++;
                    continue;
                }
                if(s[i+1]==1 && s[i+2]==1 && s[i+3]==1 && s[i+4]==0){
                    way[0][black][0]=1;
                    way[0][black][1]=i+4;
                    black++;
                    continue;
                }
            }
        }
    }
    for(i=0;i<len-2;i++){   //white
        if(s[i]==2){
            if(i>0 && s[i-1]==0){
                if(s[i+1]==2){
                    if(s[i+2]==2 && s[i+3]==0 && s[i+4]==0){    //0 2 2 2 0 0
                        way[1][white][0]=2;
                        way[1][white][1]=i-1;
                        way[1][white][2]=i+3;
                        white++;
                        continue;
                    }
                    if(s[i+2]==0 && s[i+3]==2 && s[i+4]==0){    //0 1 1 0 1 0
                        way[1][white][0]=3;
                        way[1][white][1]=i-1;
                        way[1][white][2]=i+2;
                        way[1][white][3]=i+4;
                        white++;
                        continue;
                    }
                }
                if(s[i+1]==0){
                    if(s[i+2]==2 && s[i+3]==2 && s[i+4]==0){    //0 1 0 1 1 0
                        way[1][white][0]=3;
                        way[1][white][1]=i-1;
                        way[1][white][2]=i+1;
                        way[1][white][3]=i+4;
                        white++;
                        continue;
                    }
                }
                if(s[i+1]==0 && s[i+2]==2 && s[i+3]==2 && s[i+4]==2){
                    way[1][white][0]=1;
                    way[1][white][1]=i+1;
                    white++;
                    continue;
                }
                if(s[i+1]==2 && s[i+2]==0 && s[i+3]==2 && s[i+4]==2){
                    way[1][white][0]=1;
                    way[1][white][1]=i+2;
                    white++;
                    continue;
                }
                if(s[i+1]==2 && s[i+2]==2 && s[i+3]==0 && s[i+4]==2){
                    way[1][white][0]=1;
                    way[1][white][1]=i+3;
                    white++;
                    continue;
                }
            }
            if(i==0 || s[i-1]==1){
                if(s[i+1]==0 && s[i+2]==2 && s[i+3]==2 && s[i+4]==2){
                    way[1][white][0]=1;
                    way[1][white][1]=i+1;
                    white++;
                    continue;
                }
                if(s[i+1]==2 && s[i+2]==0 && s[i+3]==2 && s[i+4]==2){
                    way[1][white][0]=1;
                    way[1][white][1]=i+2;
                    white++;
                    continue;
                }
                if(s[i+1]==2 && s[i+2]==2 && s[i+3]==0 && s[i+4]==2){
                    way[1][white][0]=1;
                    way[1][white][1]=i+3;
                    white++;
                    continue;
                }
                if(s[i+1]==2 && s[i+2]==2 && s[i+3]==2 && s[i+4]==0){
                    way[1][white][0]=1;
                    way[1][white][1]=i+4;
                    white++;
                    continue;
                }
            }
        }
    }
    //printf("black:\n%d ways to win\nways to block:\n",black);
    printf("%d ",way[0][0][0]);
    for(i=0;i<black;i++)
        for(j=1;j<=way[0][i][0];j++)
            printf("%d ",way[0][i][j]);
    //printf("\nwhite:\n%d ways to win\nways to block:\n",white);
    printf("\n%d ",way[0][0][0]);
    for(i=0;i<white;i++)
        for(j=1;j<=way[1][i][0];j++)
            printf("%d ",way[1][i][j]);
    printf("\n");
}
}
