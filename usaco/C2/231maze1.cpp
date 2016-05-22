/*
ID: s0000151
PROG: maze1
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
#define FIN {freopen("maze1.in","r",stdin);
#define FOUT freopen("maze1.out","w",stdout);}
#define Pause scanf(" ");
#define N 1
#define E 2
#define W 4
#define S 8
struct Q{
    int x:8;
    int y:7;
};
main(){
if(!DEBUG) FIN FOUT
char line[100],c;
int maze[101][40],step[101][40],i,j,w,h,ex=-2,ey,b1,b2,steps;
Q s1[2000],s2[2000],*q1,*q2,*tmp;
scanf("%d %d%c",&w,&h,&c);
for(i=0;i<h;i++){
    for(j=0;j<w;j++)maze[i][j]=15;
}
fgets(line,2*w+3,stdin);
for(i=0;i<w;i++){
    if(line[i*2+1]=='-')maze[0][i]&=~N;
}
for(i=0;i<h;i++){
    fgets(line,2*w+3,stdin);
    if(line[0]=='|')maze[i][0]&=~W;
    for(j=1;j<w;j++){
        if(line[j*2]=='|'){
            maze[i][j]&=~W;
            maze[i][j-1]&=~E;
        }
    }
    if(line[w*2]=='|')maze[i][w-1]&=~E;
    fgets(line,2*w+3,stdin);
    for(j=0;j<w;j++){
        step[i][j]=1;
        if(line[j*2+1]=='-'){
            maze[i][j]&=~S;
            maze[i+1][j]&=~N;
        }
    }
}
q1=s1;q2=s2;q1[0].x=-1;
for(j=0;j<w;j++){
    if(maze[0][j]&N){
        maze[0][j]&=~N;
        if(q1[0].x<0){q1[0].x=0;q1[0].y=j;}
        else{ex=0;ey=j;}
    }
    if(maze[h-1][j]&S){
        maze[h-1][j]&=~S;
        if(q1[0].x<0){q1[0].x=h-1;q1[0].y=j;}
        else{ex=h-1;ey=j;}
    }
}
for(i=0;i<h;i++){
    if(maze[i][0]&W){
        maze[i][0]&=~W;
        if(q1[0].x<0){q1[0].x=i;q1[0].y=0;}
        else{ex=i;ey=0;}
    }
    if(maze[i][w-1]&E){
        maze[i][w-1]&=~E;
        if(q1[0].x<0){q1[0].x=i;q1[0].y=w-1;}
        else{ex=i;ey=w-1;}
    }
}
step[q1[0].x][q1[0].y]=0;
b2=1;
if(ex!=-2){
    step[q1[1].x=ex][q1[1].y=ey]=0;
    b2++;
}
for(steps=0;b1=b2;steps++){
    for(i=b2=0;i<b1;i++){
        if(maze[q1[i].x][q1[i].y]&N && step[q1[i].x-1][q1[i].y]){
            q2[b2].x=q1[i].x-1;
            q2[b2++].y=q1[i].y;
            step[q2[b2-1].x][q2[b2-1].y]=0;
        }
        if(maze[q1[i].x][q1[i].y]&E && step[q1[i].x][q1[i].y+1]){
            q2[b2].x=q1[i].x;
            q2[b2++].y=q1[i].y+1;
            step[q2[b2-1].x][q2[b2-1].y]=0;
        }
        if(maze[q1[i].x][q1[i].y]&W && step[q1[i].x][q1[i].y-1]){
            q2[b2].x=q1[i].x;
            q2[b2++].y=q1[i].y-1;
            step[q2[b2-1].x][q2[b2-1].y]=0;
        }
        if(maze[q1[i].x][q1[i].y]&S && step[q1[i].x+1][q1[i].y]){
            q2[b2].x=q1[i].x+1;
            q2[b2++].y=q1[i].y;
            step[q2[b2-1].x][q2[b2-1].y]=0;
        }
    }
    tmp=q1;q1=q2;q2=tmp;
}
printf("%d\n",steps);
if(DEBUG) Pause
}
