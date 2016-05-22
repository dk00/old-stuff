/*
ID: s0000151
PROG: concom
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
int own[101][101],con[101][101],set[101][101];
main(){
if(!DEBUG){freopen("concom.in","r",stdin);
freopen("concom.out","w",stdout);}
int n,i,j,p,max,k;
scanf("%d",&n);
while(n--){
    scanf("%d %d %d",&i,&j,&p);
    own[i][j]+=p;
    if(p>50)con[i][j]=1;
}
for(n=1;n<=100;n++){
    for(i=1;i<=100;i++){
        for(j=1;j<=100;j++){
            if(con[i][j]==1 && !set[i][j]){
                set[i][j]=1;
                for(k=1;k<=100;k++){
                    own[i][k]+=own[j][k];
                    if(own[i][k]>50)con[i][k]=1;
                }
                con[i][j]++;
            }
        }
    }
}
for(i=1;i<=100;i++){
    for(j=1;j<=100;j++){
        if(i==j)continue;
        if(con[i][j])printf("%d %d\n",i,j);
    }
}
if(DEBUG)scanf(" ");
}
