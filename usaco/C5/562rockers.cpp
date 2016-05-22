/*
ID: s0000151
PROG: rockers
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
int n,t,m,max,best,s[20],use[20],rem[20][20];
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
void song(int d,int i);
main(){
int i,j,r[20];
freopen("rockers.in","r",stdin);
freopen("rockers.out","w",stdout);
scanf("%d %d %d",&n,&t,&m);
for(i=0;i<n;i++)scanf("%d",&r[i]);
for(j=0;j<=t*m;){
    for(max=0;use[max];max++);
    for(i=max+1;i<n;i++)
        if(!use[i] && r[i]<r[max])max=i;
    if(j+r[max]>t*m)break;
    use[max]=1;
    j+=r[max];
}
for(max=i=0;i<n;i++)
    if(use[i])s[max++]=r[i];
if(max==m){
    printf("%d\n",max);
    return 0;
}
for(best=i=0;i<m;i++)rem[0][i]=t;
song(0,0);
printf("%d\n",best);
}
void song(int d,int i){
    best>?=d;
    if(best>=max)return;
    int j,l;
    if(d)for(j=0;j<m;j++)rem[d][j]=rem[d-1][j];
    qsort(rem[d],m,sizeof(rem[0][0]),numcmp);
    for(;d+(max-i)>best && best<max;i++){
        for(j=0;j<m;j++)
            if(s[i]<=rem[d][j] && (!j || rem[d][j]!=rem[d][j-1])){
                rem[d][j]-=s[i];
                song(d+1,i+1);
                rem[d][j]+=s[i];
            }
    }
}

