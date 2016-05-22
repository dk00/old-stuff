#include<stdio.h>
#include<stdlib.h>
int **el=(int **)malloc(sizeof(int *)*1000),*temp;
const int O=0,W=1,S=2;
void qsort(int start,int end){
    if(start>=end) return;
    int p1=start+1,p2=end;
    while(1){
        for(;p1<=end && el[p1][W]<=el[start][W];p1++);
        for(;p2>start && el[p2][W]>=el[start][W];p2--);
        if(p1>=p2) break;
        temp=el[p1];
        el[p1]=el[p2];
        el[p2]=temp;
    }
    temp=el[p2];
    el[p2]=el[start];
    el[start]=temp;
    qsort(start,p2-1);
    qsort(p1,end);
}
main(){
int i,j,n,len[1000],max=0,head[1000];
for(n=0;scanf("%d %d",&i,&j)!=EOF;n++){
    el[n]=(int *)malloc(sizeof(int)*3);
    el[n][O]=n;
    el[n][W]=i;el[n][S]=j;
}
qsort(0,n-1);
for(i=0;i<n;i++){
    len[i]=1;head[i]=-1;
}
for(i=0;i<n;i++){
    for(j=0;j<i;j++){
        if(el[j][W]<el[i][W] && el[j][S]>el[i][S] && len[i]<len[j]+1){
            len[i]=len[j]+1;
            head[i]=j;
        }
    }
    max=len[max]<len[i]?i:max;
}printf("%d\n",len[max]);
int tmp[1000];
tmp[j=0]=el[max][O];
while(head[max]!=-1) tmp[++j]=el[max=head[max]][O];
for(;j>=0;j--)printf("%d\n",tmp[j]+1);
}
