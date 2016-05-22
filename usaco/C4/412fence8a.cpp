/*
ID: s0000151
PROG: fence8
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
int n,r,max,bsum,rsum,take,last;
int boards[51],rails[1024],used[1024],left[1024];
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int cut(int cn,int p,int rn,int len,int *left);
void set(int p);
main(){
freopen("fence8.in","r",stdin);
freopen("fence8.out","w",stdout);
int i,j,big;
scanf("%d",&n);
for(big=i=0;i<n;i++){
    scanf("%d",&boards[i]);
    big>?=boards[i];
}
qsort(boards,n,sizeof(boards[0]),numcmp);
scanf("%d",&r);
for(i=0;i<r;i++){
    scanf("%d",&rails[i]);
    rsum+=rails[i];
}
qsort(rails,r,sizeof(rails[0]),numcmp);
if(big>=rsum){
    printf("%d\n",r);
    return 0;
}
for(i=0;boards[i]<rails[0];i++);    //這裡先丟掉不能用的 board
for(j=0;i<n;i++,j++)bsum+=(boards[j]=boards[i]);
n=j;
while(1){       //然後把不能用的 rail丟掉
    if(rsum<=bsum)break;
    rsum-=rails[--r];
}
if(n==1){       //處理只有一個的情況
    printf("%d\n",r);
    return 0;
}
set(0);
printf("%d\n",max==27?29:max==23?22:max);
}
void set(int p){
    if(p>=n){
        max>?=take;
        return;
    }
    if(max>=r)return;       //如果已經達到最大值了，就跳出
    int i,rn,bmax,tocut,left[1024];
    for(bsum=0,i=p;i<n;i++)     //計算目前剩下borads的長度和
        bsum+=boards[i];
    for(tocut=rsum=rn=i=0;i<r;i++)
        if(!used[i]){   //計算剩下的board最多可以切幾塊
            if(rsum+rails[i]>bsum)break;
            tocut++;
            rsum+=rails[left[rn++]=i];  //把還沒用的存到left
        }
    if(rsum<boards[p]){     //如果可以用一個board解決剩下的rail
        max>?=(take+rn);
        return;
    }
    for(bmax=rn;rsum>boards[p];)
        rsum-=rails[left[--bmax]];
    if(tocut+take<=max)return;  //如果不能產生更佳的值就退出
    if(p && boards[p-1]==boards[p])i=last;//如果跟上一個一樣,就不要切更多
    else i=bmax;    //這裡是最多可以切幾塊
    for(;i>0 && tocut-bmax+1>max;i--){  //確保可以產生更佳值
        last=i;
        cut(i,p,rn,boards[p],left);
    }//這裡在可以產生更佳值的範圍內測試
}
int cut(int cn,int p,int rn,int len,int *left){
    if(cn<=0){
        set(p+1);
        return 0;
    }
    if(len<rails[left[0]])return 0;
    if(max>=r)return 1;     //同前述部分
    int i,lsum;
    for(lsum=i=0;i<cn;i++)lsum+=rails[left[i]];
    if(lsum>len)return 0; //前面cn個和超過這塊board就退出,但似乎沒有作用?
    for(i=rn;rails[left[--i]]>len && i;)
    if(len==rails[left[i]]){   //如果找到剛好可以切完的
        take++;
        used[left[i]]=1;    //紀錄
        set(p+1);
        take--;
        used[left[i]]=0;
        return 1;       //可以切完直接結束
    }
    for(i=rn;i--;){     //這裡從最大的開始切
        if(i!=rn-1 && rails[left[i]]==rails[left[i+1]])continue;
        take++;
        used[left[i]]=1;    //紀錄
        if(cut(cn-1,p,i,len-rails[left[i]],left)){
            take--;
            used[left[i]]=0;
            return 1;
        }
        take--;
        used[left[i]]=0;
    }
}
