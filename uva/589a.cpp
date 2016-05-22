#include<stdio.h>
#include<string.h>
struct P{
   int x,y,prev;
   char dir;
}p[10000];
struct Q{
   int sx,sy,bx,by,prev;
   char path[500];
}now,q[10000];
char map[20][20],tmp[500];
int n,m,len,use[20][20],box[20][20];
void inline buildpath(int i){
   if(p[i].prev)
       buildpath(p[i].prev);
   tmp[len++]=p[i].dir;
}
void inline printpath(int i){
   if(q[i].prev)printpath(q[i].prev);
   printf("%s",q[i].path);
}
int inline push(int sx,int sy,int bx,int by,int dx,int dy){
   if(bx+dx<0 || bx+dx>=n || by+dy<0 || by+dy>=m ||
      map[bx+dx][by+dy]=='#')return 0;
int i,j;
   for(i=0;i<20;i++)
       for(j=0;j<20;j++)
           use[i][j]=(map[i][j]=='.');
   p[0]=(P){sx,sy,0,0};
   for(i=0,j=1;i<j;i++){
       sx=p[i].x,sy=p[i].y;
       if(sx+dx==bx && sy+dy==by)break;
       if(sx && use[sx-1][sy]){
           use[sx-1][sy]=0;
           p[j++]=(P){sx-1,sy,i,'n'};
       }
       if(sy && use[sx][sy-1]){
           use[sx][sy-1]=0;
           p[j++]=(P){sx,sy-1,i,'w'};
       }
       if(sx+1<n && use[sx+1][sy]){
           use[sx+1][sy]=0;
           p[j++]=(P){sx+1,sy,i,'s'};
       }
       if(sy+1<m && use[sx][sy+1]){
           use[sx][sy+1]=0;
           p[j++]=(P){sx,sy+1,i,'e'};
       }
   }
   len=0;
   buildpath(i);
   tmp[len]=0;
   return(sx+dx==bx && sy+dy==by);
}
main(){
int i,j,sx,sy,tx,ty,bx,by,C=0;
char c;
while(scanf("%d %d%c",&n,&m,&c) && n+m){
   for(i=0;i<n;i++){
       gets(map[i]);
       for(j=0;j<m;j++){
           box[i][j]=(map[i][j]!='#');
           if(map[i][j]=='S')
               sx=i,sy=j,map[i][j]='.';
           if(map[i][j]=='B')
               bx=i,by=j,map[i][j]='.';
           if(map[i][j]=='T')
               tx=i,ty=j,map[i][j]='.';
       }
   }
   box[bx][by]=0;
   q[0].sx=sx,q[0].sy=sy,q[0].bx=bx,q[0].by=by;
   for(i=0,j=1;i<j;i++){
       sx=q[i].sx,sy=q[i].sy,bx=q[i].bx,by=q[i].by;
       if(bx==tx && by==ty)break;
       map[sx][sy]='S',map[bx][by]='B';
       now=q[i];
       now.prev=i;
       q[j]=now;
       q[j].sx=bx,q[j].sy=by,q[j].bx=bx-1,q[j].by=by;
       if(bx && box[bx-1][by] && push(sx,sy,bx,by,-1,0))
           strcpy(q[j++].path,strcat(tmp,"N")),box[bx-1][by]=0;
       q[j]=now;
       q[j].sx=bx,q[j].sy=by,q[j].bx=bx,q[j].by=by-1;
       if(by && box[bx][by-1] && push(sx,sy,bx,by,0,-1))
           strcpy(q[j++].path,strcat(tmp,"W")),box[bx][by-1]=0;
       q[j]=now;
       q[j].sx=bx,q[j].sy=by,q[j].bx=bx+1,q[j].by=by;
       if(bx+1<n && box[bx+1][by] && push(sx,sy,bx,by,1,0))
           strcpy(q[j++].path,strcat(tmp,"S")),box[bx+1][by]=0;
       q[j]=now;
       q[j].sx=bx,q[j].sy=by,q[j].bx=bx,q[j].by=by+1;
       if(by+1<m && box[bx][by+1] && push(sx,sy,bx,by,0,1))
           strcpy(q[j++].path,strcat(tmp,"E")),box[bx][by+1]=0;
       map[sx][sy]='.',map[bx][by]='.';
   }
   printf("Maze #%d\n",++C);
   if(bx==tx && by==ty){
       printpath(i);
       puts("");
   }
   else puts("Impossible.");
   puts("");
}
}
