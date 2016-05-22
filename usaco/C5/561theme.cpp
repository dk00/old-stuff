/*
ID: s0000151
PROG: theme
LANG: C++
*/
#include<stdio.h>
main(){
freopen("theme.in","r",stdin);
freopen("theme.out","w",stdout);
int i,j,k,n,max=0,d[5000];
scanf("%d %d",&n,&j);
for(i=1;i<n;i++){
    scanf("%d",&k);
    d[i-1]=j-k;
    j=k;
}
for(i=3;i<n-1;i++)    //offset
    for(k=j=0;j+i<n-1;j++){
        if(d[i+j]==d[j])k++;
        else k=0;
        max>?=((k+1)<?i);
    }
printf("%d\n",max>=5?max:0);
}
