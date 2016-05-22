/*
ID: s0000151
PROG: ariprog
LANG: C++
*/

#include<stdio.h>
int p2[251],s[126000];
main(){
//freopen("ariprog.in","r",stdin);
//freopen("ariprog.out","w",stdout);
int i,j,k,l,n,m,max,a[10000],d[10000];
scanf("%d %d",&n,&m);
for(max=m*m*2,i=0;i<=m;i++)p2[i]=i*i;
for(i=0;i<=m;i++)
    for(j=i;j<=m;j++)s[p2[i]+p2[j]]=1;
for(m=0,i=max;i>=n-1;i--){
    if(!s[i])continue;
    for(j=1;j*n-j<=i;j++){
        if(s[i-j] && s[i-j-j])for(k=3,l=i-j-j;k<n && s[l-j];l-=j,k++);
        if(k==n){a[m]=l;d[m++]=j;k=0;}
    }
}
for(i=0;i<m;i++)
    for(j=1;j<m;j++)
        if(a[j]>a[j-1]){
            k=a[j];a[j]=a[j-1];a[j-1]=k;
            k=d[j];d[j]=d[j-1];d[j-1]=k;
        }
for(i=0;i<m;i++)
    for(j=1;j<m;j++)
        if(d[j]>d[j-1]){
            k=a[j];a[j]=a[j-1];a[j-1]=k;
            k=d[j];d[j]=d[j-1];d[j-1]=k;
        }
if(!m)puts("NONE");
else while(m--)printf("%d %d\n",a[m],d[m]);
}
