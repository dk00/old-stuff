/* @JUDGE_ID:  58589NF  103  C++  "Stacking Boxes"*/
#include<stdio.h>
#include<stdlib.h>
int k,n,i,j,**box,*temp,ori[30];
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int p;
int nest(int a,int b){
    for(p=0;p<n;p++){
        if(box[a][p]>=box[b][p])
            return 0;
    }
    return 1;
}
int arcmp(int a,int b){
    for(p=0;p<n;p++){
        if(box[a][p]!=box[b][p])
            return box[a][p]-box[b][p];
    }
    return 0;
}
void qsort2(int start,int end){
    if(start>=end) return;
    int p1=start+1,p2=end;
    while(1){
        for(;p1<=end && arcmp(p1,start)<=0;p1++);
        for(;p2>start && arcmp(p2,start)>=0;p2--);
        if(p1>=p2)break;
        temp=box[p2];
        box[p2]=box[p1];
        box[p1]=temp;
        p=ori[p2];
        ori[p2]=ori[p1];
        ori[p1]=p;
    }
    temp=box[p2];
    box[p2]=box[start];
    box[start]=temp;
    p=ori[p2];
    ori[p2]=ori[start];
    ori[start]=p;
    qsort2(start,p2-1);
    qsort2(p1,end);
}
main(){
box=(int **)malloc(sizeof(int *)*30);
for(i=0;i<30;i++) box[i]=(int *)malloc(sizeof(int)*10);
int next[30],len[30],max;
while(scanf("%d %d",&k,&n)!=EOF){
    for(i=0;i<k;i++){
        ori[i]=i;
        for(j=0;j<n;j++)
            scanf("%d",&box[i][j]);
        if(n>1)qsort((void *)box[i],n,sizeof(int),numcmp);
        next[i]=-1;len[i]=1;
    }
    qsort2(0,k-1);
    max=0;
    for(i=k-2;i>=0;i--){
        for(j=k-1;j>i;j--){
            if(nest(i,j) && len[i]<=len[j]+1){
                next[i]=j;
                len[i]=len[j]+1;
            }
            if(len[i]>len[max]) max=i;
        }
    }
    printf("%d\n%d",len[max],ori[max]+1);
    max=next[max];
    for(;max!=-1;max=next[max])
        printf(" %d",ori[max]+1);
    printf("\n");
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
