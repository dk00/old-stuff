#include<stdio.h>
#define MAXN 250
struct RECT{
    int sx,sy,ex,ey,cost;
}rect[10000];
int map[MAXN+1][MAXN+1],reh[MAXN+1][MAXN+1];
main(){
int r,c;    //Limit of the map
int n,k;    //Data
int x,y;    //position
int i,j,p,q,rn,sum,min=2147483647;
//read data
scanf("%d %d %d %d",&r,&c,&n,&k);
for(i=0;i<n;i++){
    scanf("%d %d",&x,&y);
    map[x][y]++;
}
//pre-process for DP
for(i=1;i<=r;i++)
    for(j=1;j<=c;j++)
        map[i][j]+=map[i-1][j];
//main DP solve
for(rn=0,i=1;i<=r;i++){                //start from row i
    for(p=1;p+i-1<=r;p++){              //take p rows
        for(sum=0,j=q=1;j<=c;j++){  //start from col r to j
            sum+=map[i+p-1][j]-map[i-1][j];
            while(sum>k && q<j){
                sum-=map[i+p-1][q]-map[i-1][q];
                q++;
            }
            if(sum==k && q>reh[i][j]){
                rect[rn].sx=i,rect[rn].sy=q;
                rect[rn].ex=i+p-1,rect[rn].ey=j;
                rect[rn].cost=(2+rect[rn].ex-rect[rn].sx+rect[rn].ey-
                rect[rn].sy)*2,rn++;
                reh[i][j]=q;
            }
            while(sum>=k && q<j){
                sum-=map[i+p-1][q]-map[i-1][q];
                q++;
            }
            while(map[i+p-1][q]-map[i-1][q]<=0)q++;
        }
    }
}
for(i=0;i<rn;i++)
    for(j=i+1;j<rn;j++){
        if(rect[i].sx>rect[j].ex || rect[i].sy>rect[j].ey)
            min<?=(rect[i].cost+rect[j].cost);
        else if(rect[j].sx>rect[i].ex || rect[j].sy>rect[i].ey)
            min<?=(rect[i].cost+rect[j].cost);
    }
if(min>=(r+c)*4)puts("NO");
else printf("%d\n",min);
}
