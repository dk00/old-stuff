#include<stdio.h>
int m,n,dx[]={0,1,0,-1},dy[]={1,0,-1,0},lost[51][51];
char dir[]="NESW";
class robot{
public:
    int x,y,d;
    void set(char *c);
    void command(char *c);
}hello;
void robot::set(char *c){
    sscanf(c,"%d %d %c",&x,&y,&c[0]);
    if(c[0]=='N')d=0;
    else if(c[0]=='E')d=1;
    else if(c[0]=='S')d=2;
    else d=3;
}
void robot::command(char *c){
    if(c[0]=='\0'){
        printf("%d %d %c\n",x,y,dir[d]);
        return;
    }
    if(c[0]=='L')d=(d+3)%4;
    else if(c[0]=='R')d=(d+1)%4;
    else if(x+dx[d]<=m && y+dy[d]<=n && x+dx[d]>=0 && y+dy[d]>=0){
        x+=dx[d];
        y+=dy[d];
    }
    else if(!lost[x][y]){
        lost[x][y]=1;
        printf("%d %d %c LOST\n",x,y,dir[d]);
        return;
    }
    command(&c[1]);
}
main(){
char s[105];
scanf("%d %d%c",&m,&n,&s[1]);
while(gets(s)!=NULL){
    hello.set(s);
    hello.command(gets(s));
}
}
