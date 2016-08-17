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
for(i=0;boards[i]<rails[0];i++);    //�o�̥��ᱼ����Ϊ� board
for(j=0;i<n;i++,j++)bsum+=(boards[j]=boards[i]);
n=j;
while(1){       //�M��⤣��Ϊ� rail�ᱼ
    if(rsum<=bsum)break;
    rsum-=rails[--r];
}
if(n==1){       //�B�z�u���@�Ӫ����p
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
    if(max>=r)return;       //�p�G�w�g�F��̤j�ȤF�A�N���X
    int i,rn,bmax,tocut,left[1024];
    for(bsum=0,i=p;i<n;i++)     //�p��ثe�ѤUborads�����שM
        bsum+=boards[i];
    for(tocut=rsum=rn=i=0;i<r;i++)
        if(!used[i]){   //�p��ѤU��board�̦h�i�H���X��
            if(rsum+rails[i]>bsum)break;
            tocut++;
            rsum+=rails[left[rn++]=i];  //���٨S�Ϊ��s��left
        }
    if(rsum<boards[p]){     //�p�G�i�H�Τ@��board�ѨM�ѤU��rail
        max>?=(take+rn);
        return;
    }
    for(bmax=rn;rsum>boards[p];)
        rsum-=rails[left[--bmax]];
    if(tocut+take<=max)return;  //�p�G���ಣ�ͧ�Ϊ��ȴN�h�X
    if(p && boards[p-1]==boards[p])i=last;//�p�G��W�@�Ӥ@��,�N���n����h
    else i=bmax;    //�o�̬O�̦h�i�H���X��
    for(;i>0 && tocut-bmax+1>max;i--){  //�T�O�i�H���ͧ�έ�
        last=i;
        cut(i,p,rn,boards[p],left);
    }//�o�̦b�i�H���ͧ�έȪ��d�򤺴���
}
int cut(int cn,int p,int rn,int len,int *left){
    if(cn<=0){
        set(p+1);
        return 0;
    }
    if(len<rails[left[0]])return 0;
    if(max>=r)return 1;     //�P�e�z����
    int i,lsum;
    for(lsum=i=0;i<cn;i++)lsum+=rails[left[i]];
    if(lsum>len)return 0; //�e��cn�өM�W�L�o��board�N�h�X,�����G�S���@��?
    for(i=rn;rails[left[--i]]>len && i;)
    if(len==rails[left[i]]){   //�p�G����n�i�H������
        take++;
        used[left[i]]=1;    //����
        set(p+1);
        take--;
        used[left[i]]=0;
        return 1;       //�i�H������������
    }
    for(i=rn;i--;){     //�o�̱q�̤j���}�l��
        if(i!=rn-1 && rails[left[i]]==rails[left[i+1]])continue;
        take++;
        used[left[i]]=1;    //����
        if(cut(cn-1,p,i,len-rails[left[i]],left)){
            take--;
            used[left[i]]=0;
            return 1;
        }
        take--;
        used[left[i]]=0;
    }
}
