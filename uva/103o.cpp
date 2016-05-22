/* @JUDGE_ID:  58589NF  103  c  ""*/
#include<stdio.h>
#include<stdlib.h>
int **temp;
int **box;
int n,ci;
int numcmp(const void *a,const void *b){
return *(int *)a-*(int *)b;
}
int pcmp(int a,int b){
for(ci=0;ci<n;ci++){
    if(box[a][ci]>=box[b][ci])
	   return box[a][ci]-box[b][ci];
}
return box[a][n-1]-box[b][n-1];
}
void psort(int start,int end){
    if(start>=end)
	   return;
    int mid=(start+end)/2;
    psort(start,mid);
    psort(mid+1,end);
    int p=start,p1=start,p2=mid+1;
    while(p<=end){
	   if(p1>mid)
		  temp[p++]=box[p2++];
	   else if(p2>end)
		  temp[p++]=box[p1++];
	   else if(pcmp(p2,p1)>0)
		  temp[p++]=box[p1++];
	   else
		  temp[p++]=box[p2++];
    }
    for(p=start;p<=end;p++)
	   box[p]=temp[p];
    return;
}
int main(){
int k,head[25],len[25],i,j,max,tp[25];
while(scanf("%d %d",&k,&n)!=EOF){
    box=(int **)malloc(sizeof(int *)*k);
    for(i=0;i<k;i++){
	   box[i]=(int *)malloc(sizeof(int)*(n+1));
	   for(j=0;j<n;j++)
		  scanf("%d",&box[i][j]);
	   head[i]=-1;
	   len[i]=1;
	   if(n>1)qsort((void *)box[i],n,sizeof(int),numcmp);
	   box[i][n]=i+1;
    }
//    psort(0,k-1);
    max=0;
    for(i=0;i<k;i++){
	   for(j=0;j<k;j++){
		  if(pcmp(j,i)<0 && len[i]<len[j]+1){
			 len[i]=len[j]+1;
			 head[i]=j;
			 if(len[i]>len[max])
				max=i;
		  }
		  if(head[j]>=0 && len[i]<=len[j]+1 && pcmp(j,i)<0
		  && pcmp(head[i],j)<0){
			 len[i]=len[j]+1;
			 head[i]=j;
			 if(len[i]>len[max])
				max=i;
		  }
	   }
    }
    for(i=max,j=0;head[i]>=0;i=head[i])
	   tp[j++]=box[i][n];
    tp[j]=box[i][n];
    printf("%d\n",len[max]);
    for(j=j;j>=0;j--){
	   printf("%d ",tp[j]);
    }
    printf("\n");
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
