/* @JUDGE_ID:  58589NF  532  C++  "Dungeon Master"*/
#include<stdio.h>
#include<stdlib.h>
struct workq{
    int x,y,z;
    workq *next;
};
int main(){
int l,r,c,i,j,k,sx,sy,sz,dgn[30][30][30],timen;
workq *last=(workq *)malloc(sizeof(workq)),*now,*top;
char line[50];
while(1){
    scanf("%d %d %d",&l,&r,&c);
    if(l*r*c==0)
        break;
    now=last;
    top=now;
    now->next=(workq *)malloc(sizeof(workq));
    now->next->x=-1;
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
        if(now->x<0){
            printf("Trapped!\n");
            break;
        }
        if(now->x==sx && now->y==sy && now->z==sz){
            printf("Escaped in %d minute(s).\n",
            dgn[now->x][now->y][now->z]);
            break;
        }
        timen=dgn[now->x][now->y][now->z];
        if(now->x-1>=0 && dgn[now->x-1][now->y][now->z]>timen){
            dgn[now->x-1][now->y][now->z]=timen+1;
            if(top->next->next==NULL || top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=(workq *)malloc(sizeof(workq));
                top->next->next->next=NULL;
            }
            top=top->next;
            top->next->x=-1;
            top->x=now->x-1;
            top->y=now->y;
            top->z=now->z;
        }
        if(now->y-1>=0 && dgn[now->x][now->y-1][now->z]>timen){
            dgn[now->x][now->y-1][now->z]=timen+1;
            if(top->next->next==NULL || top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=(workq *)malloc(sizeof(workq));
                top->next->next->next=NULL;
            }
            top=top->next;
            top->next->x=-1;
            top->x=now->x;
            top->y=now->y-1;
            top->z=now->z;
        }
        if(now->z-1>=0 && dgn[now->x][now->y][now->z-1]>timen){
            dgn[now->x][now->y][now->z-1]=timen+1;
            if(top->next->next==NULL || top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=(workq *)malloc(sizeof(workq));
                top->next->next->next=NULL;
            }
            top=top->next;
            top->next->x=-1;
            top->x=now->x;
            top->y=now->y;
            top->z=now->z-1;
        }
        if(now->x+1<l && dgn[now->x+1][now->y][now->z]>timen){
            dgn[now->x+1][now->y][now->z]=timen+1;
            if(top->next->next==NULL || top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=(workq *)malloc(sizeof(workq));
                top->next->next->next=NULL;
            }
            top=top->next;
            top->next->x=-1;
            top->x=now->x+1;
            top->y=now->y;
            top->z=now->z;
        }
        if(now->y+1<r && dgn[now->x][now->y+1][now->z]>timen){
            dgn[now->x][now->y+1][now->z]=timen+1;
            if(top->next->next==NULL || top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=(workq *)malloc(sizeof(workq));
                top->next->next->next=NULL;
            }
            top=top->next;
            top->next->x=-1;
            top->x=now->x;
            top->y=now->y+1;
            top->z=now->z;
        }
        if(now->z+1<c && dgn[now->x][now->y][now->z+1]>timen){
            dgn[now->x][now->y][now->z+1]=timen+1;
            if(top->next->next==NULL || top->next==now){
                top->next=(workq *)malloc(sizeof(workq));
                top->next->next=(workq *)malloc(sizeof(workq));
                top->next->next->next=NULL;
            }
            top=top->next;
            top->next->x=-1;
            top->x=now->x;
            top->y=now->y;
            top->z=now->z+1;
        }
        now->x=-1;
        top->next=now;
        now=now->next;
    }
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
