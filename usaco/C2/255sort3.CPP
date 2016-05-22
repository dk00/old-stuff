/*
ID: s0000151
PROG: sort3
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
#define swap(a,b) t=(a);(a)=(b);(b)=t;swapn++
main(){
if(!DEBUG){freopen("sort3.in","r",stdin);
freopen("sort3.out","w",stdout);}
int n,s[1001],i,j,r[4]={0,0,0,0},t,swapn=0;
scanf("%d",&n);
for(i=1;i<=n;i++){
    scanf("%d",&s[i]);
    r[s[i]]++;
}
r[2]+=r[1];r[3]+=r[2];
for(j=1,i=r[1]+1;i<=r[2];i++){
    if(s[i]==1){
        for(j=1;j<=r[1] && s[j]!=2;j++);
        if(j<=r[1]){t=s[i];s[i]=s[j];s[j]=t;swapn++;}
    }
    if(j>r[1])break;
}
for(j=1,i=r[2]+1;i<=r[3];i++){
    if(s[i]==1){
        for(j=1;j<=r[1] && s[j]!=3;j++);
        if(j<=r[1]){t=s[i];s[i]=s[j];s[j]=t;swapn++;}
    }
    if(j>r[1])break;
}
for(j=1,i=r[1]+1;i<=r[3];i++){
    if(s[i]==1){
        for(j=1;j<=r[1] && s[j]==1;j++);
        if(j<=r[1]){t=s[i];s[i]=s[j];s[j]=t;swapn++;}
    }
    if(j>r[1])break;
}
for(j=r[1]+1,i=r[2]+1;i<=r[3];i++){
    if(s[i]==2){
        for(j=r[1]+1;j<=r[2] && s[j]==2;j++);
        if(j<=r[2]){t=s[i];s[i]=s[j];s[j]=t;swapn++;}
    }
    if(j>r[2])break;
}
printf("%d\n",swapn);
if(DEBUG)scanf(" ");
}
