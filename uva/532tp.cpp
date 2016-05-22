/* @JUDGE_ID:  58589NF  532  C++  "Dungeon Master"*/
#include<stdio.h>
#include<stdlib.h>
int main(){
char dox[10000],doy[10000],doz[10000]
int l,r,c,i,j,k,sx,sy,sz,dgn[30][30][30],timen,list[10000];
int now,top;
char line[50];
while(1){
    scanf("%d %d %d",&l,&r,&c);
    if(l*r*c==0)
        break;
    now=0;
    top=1;
    for(i=0;i<l;i++){
        gets(line);
        for(j=0;j<r;j++){
            gets(line);
            for(k=0;k<c;k++){
                if(line[k]=='#')
                    dgn[i][j][k]=-1;
                else if(line[k]=='E'){
                    dgn[i][j][k]=0;
                    dox[now]=i;
                    doy[now]=j;
                    doz[now]=k;
                }
                else if(line[k]=='S'){
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
        if(now==NULL){
            printf("Trapped!\n");
            break;
        }
        if(dox[now]==sx && doy[now]==sy && doz[now]==sz){
            printf("Escaped in %d minute(s).\n",
            dgn[dox[now]][doy[now]][doz[now]]);
            break;
        }
        timen=dgn[dox[now]][doy[now]][doz[now]];
        if(dox[now]-1>=0 && dgn[dox[now]-1][doy[now]][doz[now]]>timen){
            dgn[dox[now]-1][doy[now]][doz[now]]=timen+1;
            top->next=(workq *)malloc(sizeof(workq));
            top=top->next;
            dox[top]=dox[now]-1;
            doy[top]=doy[now];
            doz[top]=doz[now];
            top->next=NULL;
        }
        if(doy[now]-1>=0 && dgn[dox[now]][doy[now]-1][doz[now]]>timen){
            dgn[dox[now]][doy[now]-1][doz[now]]=timen+1;
            top->next=(workq *)malloc(sizeof(workq));
            top=top->next;
            dox[top]=dox[now];
            doy[top]=doy[now]-1;
            doz[top]=doz[now];
            top->next=NULL;
        }
        if(doz[now]-1>=0 && dgn[dox[now]][doy[now]][doz[now]-1]>timen){
            dgn[dox[now]][doy[now]][doz[now]-1]=timen+1;
            top->next=(workq *)malloc(sizeof(workq));
            top=top->next;
            dox[top]=dox[now];
            doy[top]=doy[now];
            doz[top]=doz[now]-1;
            top->next=NULL;
        }
        if(dox[now]+1<l && dgn[dox[now]+1][doy[now]][doz[now]]>timen){
            dgn[dox[now]+1][doy[now]][doz[now]]=timen+1;
            top->next=(workq *)malloc(sizeof(workq));
            top=top->next;
            dox[top]=dox[now]+1;
            doy[top]=doy[now];
            doz[top]=doz[now];
            top->next=NULL;
        }
        if(doy[now]+1<r && dgn[dox[now]][doy[now]+1][doz[now]]>timen){
            dgn[dox[now]][doy[now]+1][doz[now]]=timen+1;
            top->next=(workq *)malloc(sizeof(workq));
            top=top->next;
            dox[top]=dox[now];
            doy[top]=doy[now]+1;
            doz[top]=doz[now];
            top->next=NULL;
        }
        if(doz[now]+1<c && dgn[dox[now]][doy[now]][doz[now]+1]>timen){
            dgn[dox[now]][doy[now]][doz[now]+1]=timen+1;
            top->next=(workq *)malloc(sizeof(workq));
            top=top->next;
            dox[top]=dox[now];
            doy[top]=doy[now];
            doz[top]=doz[now]+1;
            top->next=NULL;
        }
        last=now;
        now=now->next;
    }
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
