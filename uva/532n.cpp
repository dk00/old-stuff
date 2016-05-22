/* @JUDGE_ID:  58589NF  532  C++  "Dungeon Master"*/
#include<stdio.h>
#include<stdlib.h>
struct workq{
    int x,y,z;
    workq *next;
};
int main(){
int l,r,c,i,j,k,sx,sy,sz,dgn[31][31][31],timen;
workq *begin=(workq *)malloc(sizeof(workq)),*now,*top;
begin->next=(workq *)malloc(sizeof(workq));
begin->next->next=begin;
char line[50];
while(1){
    scanf("%d %d %d",&l,&r,&c);
    if(l*r*c==0)
        break;
    now=begin;
    top=now->next;
    for(i=0;i<l;i++){
        gets(line);
        for(j=0;j<r;j++){
            gets(line);
            for(k=0;k<c;k++){
                if(line[k]=='#')
                    dgn[i][j][k]=-1;
                else if(line[k]=='S'){
                    dgn[i][j][k]=0;
                    now->x=i;
                    now->y=j;
                    now->z=k;
                }
                else if(line[k]=='E'){
				dgn[i][j][k]=32767;
                    sx=i;
                    sy=j;
                    sz=k;
                }
                else
                    dgn[i][j][k]=32767;
            }
        }
    }
    while(1){
        if(now==top){
            printf("Trapped!\n");
            break;
        }
        if(now->x==sx && now->y==sy && now->z==sz){
            printf("Escaped in %d minute(s).\n",
            dgn[now->x][now->y][now->z]);
            break;
        }
        timen=dgn[now->x][now->y][now->z]+1;

        if(now->x>0 && dgn[now->x-1][now->y][now->z]>timen){
            top->x=now->x-1;top->y=now->y;top->z=now->z;
            dgn[now->x-1][now->y][now->z]=timen;
            if(top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=now;
            }
            top=top->next;
        }
        if(now->x+1<l && dgn[now->x+1][now->y][now->z]>timen){
            top->x=now->x+1;top->y=now->y;top->z=now->z;
            dgn[now->x+1][now->y][now->z]=timen;
            if(top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=now;
            }
            top=top->next;
        }
        if(now->y>0 && dgn[now->x][now->y-1][now->z]>timen){
            top->x=now->x;top->y=now->y-1;top->z=now->z;
            dgn[now->x][now->y-1][now->z]=timen;
            if(top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=now;
            }
            top=top->next;
        }
        if(now->y+1<r && dgn[now->x][now->y+1][now->z]>timen){
            top->x=now->x;top->y=now->y+1;top->z=now->z;
            dgn[now->x][now->y+1][now->z]=timen;
            if(top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=now;
            }
            top=top->next;
        }
        if(now->z>0 && dgn[now->x][now->y][now->z-1]>timen){
            top->x=now->x;top->y=now->y;top->z=now->z-1;
            dgn[now->x][now->y][now->z-1]=timen;
            if(top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=now;
            }
            top=top->next;
        }
        if(now->z+1<c && dgn[now->x][now->y][now->z+1]>timen){
            top->x=now->x;top->y=now->y;top->z=now->z+1;
            dgn[now->x][now->y][now->z+1]=timen;
            if(top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=now;
            }
            top=top->next;
        }
        now=now->next;
    }
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
