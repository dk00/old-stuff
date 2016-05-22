/*
ID: s0000151
PROG: castle
LANG: C++
*/
#define N 2
#define E 4
#define W 1
#define S 8
#include<stdio.h>
int wall[51][51],w,z,size[2500],ctl[51][51],k,d;
void set(int x,int y){
    if(ctl[x][y]!=-1)return;
    ctl[x][y]=k;
    size[k]++;
    if((wall[x][y]&N)==0 && x>0)set(x-1,y);
    if((wall[x][y]&E)==0 && y<w)set(x,y+1);
    if((wall[x][y]&W)==0 && y>0)set(x,y-1);
    if((wall[x][y]&S)==0 && x<z)set(x+1,y);
}
main(){
freopen("castle.in","r",stdin);
freopen("castle.out","w",stdout);
int i,j,max=0,px=0,py=99;
scanf("%d %d",&w,&z);
for(i=0;i<z;i++){
    for(j=0;j<w;j++){
        scanf("%d",&wall[i][j]);
        ctl[i][j]=-1;
    }
}
for(i=0,k=0;i<z;i++){
    for(j=0;j<w;j++){
        if(ctl[i][j]<0){
            set(i,j);
            if(size[k]>size[max])max=k;
            k++;
        }
    }
}
printf("%d\n%d\n",k,size[max]);
for(i=1,max=0,j=w-1;i<z;i++){
    if(ctl[i][j]!=ctl[i-1][j]){
        if(size[ctl[i-1][j]]+size[ctl[i][j]]>=max){
            px=i;py=j;d=N;
            max=size[ctl[i-1][j]]+size[ctl[i][j]];
        }
    }
}
for(j=w-2;j>=0;j--){
    if(ctl[0][j]!=ctl[0][j+1]){
        if(size[ctl[0][j+1]]+size[ctl[0][j]]>=max){
            px=0;py=j;d=E;
            max=size[ctl[0][j+1]]+size[ctl[0][j]];
        }
    }
    for(i=1;i<z;i++){
        if(ctl[i][j]!=ctl[i][j+1]){
            if(size[ctl[i][j+1]]+size[ctl[i][j]]>=max){
                px=i;py=j;d=E;
                max=size[ctl[i][j+1]]+size[ctl[i][j]];
            }
        }
        if(ctl[i][j]!=ctl[i-1][j]){
            if(size[ctl[i-1][j]]+size[ctl[i][j]]>=max){
                px=i;py=j;d=N;
                max=size[ctl[i-1][j]]+size[ctl[i][j]];
            }
        }
    }
}
printf("%d\n%d %d ",max,px+1,py+1);
if(d==E)printf("E\n");
else printf("N\n");
//scanf(" ");
}
