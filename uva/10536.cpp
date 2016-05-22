#include<stdio.h>
int board[4][4],cut[65536],win[65536];
int _i,_j,_tmp;
inline int calc(){
    for(_tmp=_i=0;_i<4;_i++)
        for(_j=0;_j<4;_j++)
            _tmp|=board[_i][_j]<<(_i*4+_j);
    return _tmp;
}
inline int play(){
    if(cut[calc()])return win[_tmp];
    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<4;j++){
            if(!board[i][j]&&i+2<4&&!board[i+1][j]&&!board[i+2][j]){
                board[i][j]=board[i+1][j]=board[i+2][j]=1;
                if(!play()){
                    cut[calc()]=1;
                    win[_tmp]=1;
                    board[i][j]=board[i+1][j]=board[i+2][j]=0;
                    return 1;
                }
                board[i][j]=board[i+1][j]=board[i+2][j]=0;
            }
            if(!board[i][j]&&j+2<4&&!board[i][j+1]&&!board[i][j+1]){
                board[i][j]=board[i][j+1]=board[i][j+2]=1;
                if(!play()){
                    cut[calc()]=1;
                    win[_tmp]=1;
                    board[i][j]=board[i][j+1]=board[i][j+2]=0;
                    return 1;
                }
                board[i][j]=board[i][j+1]=board[i][j+2]=0;
            }
            if(!board[i][j] && i+1<4 && !board[i+1][j]){
                board[i][j]=board[i+1][j]=1;
                if(!play()){
                    cut[calc()]=1;
                    win[_tmp]=1;
                    board[i][j]=board[i+1][j]=0;
                    return 1;
                }
                board[i][j]=board[i+1][j]=0;
            }
            if(!board[i][j] && j+1<4 && !board[i][j+1]){
                board[i][j]=board[i][j+1]=1;
                if(!play()){
                    cut[calc()]=1;
                    win[_tmp]=1;
                    board[i][j]=board[i][j+1]=0;
                    return 1;
                }
                board[i][j]=board[i+1][j]=0;
            }
            if(!board[i][j]){
                board[i][j]=1;
                if(!play()){
                    cut[calc()]=1;
                    win[_tmp]=1;
                    board[i][j]=0;
                    return 1;
                }
                board[i][j]=0;
            }
        }
    cut[calc()]=1;
    return 0;
}
main(){
cut[65536]=1;
int i,j,n;
scanf("%d",&n);
char s[4][5];
while(n--){
    for(i=0;i<4;i++)scanf("%s",s[i]);
    for(i=0;i<4;i++)
        for(j=0;j<4;j++)
            board[i][j]=(s[i][j]=='x');
    puts(play()?"WINNING":"LOSING");
}
}
