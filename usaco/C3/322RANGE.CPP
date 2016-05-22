/*
ID: s0000151
PROG: range
LANG: C++
*/

#include<stdio.h>
#define DEBUG 0
long s[251][251],sum[251];
main(){
if(!DEBUG){freopen("range.in","r",stdin);
freopen("range.out","w",stdout);}
long n,i,j;
scanf("%ld",&n);getchar();
s[0][0]=getchar()-'0';
for(i=0;i<n;i++)sum[i]=0;
for(i=1;i<n;i++)s[0][i]=getchar()-'0';
for(getchar(),i=1;i<n;i++){
    s[i][0]=getchar()-'0';
    for(j=1;j<n;j++){
        s[i][j]=getchar()-'0';
        if(s[i][j])s[i][j]+=s[i-1][j]<?s[i][j-1]<?s[i-1][j-1];
        if(s[i][j]>=2)sum[s[i][j]]++;
    }
    getchar();
}
for(i=n;i-->2;)sum[i]+=sum[i+1];
for(i=2;i<=n;i++)if(sum[i])printf("%ld %ld\n",i,sum[i]);
if(DEBUG)scanf(" ");
}
