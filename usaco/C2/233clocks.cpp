/*
ID: s0000151
PROG: clocks
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
#define FIN if(!DEBUG){freopen("clocks.in","r",stdin);
#define FOUT freopen("clocks.out","w",stdout);}
#define FILE FIN FOUT
#define Pause if(DEBUG)scanf(" ");
 /*
 /1     1245
 /2     123
 /3 	2356
 /4 	147
 /5 	24568
 /6 	369
 /7     4578
 /8     789
 /9     5689
*/
long clock[9],path[27],d,k,used[9],affect[9][9]={
{1,1,0,1,1,0,0,0,0},{1,1,1,0,0,0,0,0,0},{0,1,1,0,1,1,0,0,0},
{1,0,0,1,0,0,1,0,0},{0,1,0,1,1,1,0,1,0},{0,0,1,0,0,1,0,0,1},
{0,0,0,1,1,0,1,1,0},{0,0,0,0,0,0,1,1,1},{0,0,0,0,1,1,0,1,1}},max;
int dfs(int n){
    if((clock[0]+clock[1]+clock[2]+clock[3]+clock[4]+clock[5]+
    clock[6]+clock[7]+clock[8])==0)return 1;
    if(d>=max)return 0;
    for(;n<(10-(max/3)+(d/3)) && n<9;n++){
        if(used[n]<3){
            used[n]++;
            for(k=0;k<9;k++){
                if(affect[n][k])clock[k]=(clock[k]+1)%4;
            }
            path[d++]=n;
            if((n<8 || used[8]<=3) && dfs(n))return 1;
            d--;
            for(k=0;k<9;k++){
                if(affect[n][k])clock[k]=(clock[k]+3)%4;
            }
            used[n]--;
        }
    }
    return 0;
}
main(){
FILE
int i,n;
for(i=0;i<9;i++){
    scanf("%d",&n);
	clock[i]=(n%12)/3;
    used[i]=0;
}
for(max=1;max<=27;max++){
    if(dfs(d=0))break;
}
for(printf("%d",path[0]+1),i=1;i<max;i++)printf(" %d",path[i]+1);
puts("");
Pause
}
