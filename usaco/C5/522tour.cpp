/*
ID: s0000151
PROG: tour
LANG: C++
*/
#include<stdio.h>
#include<string.h>
main(){
freopen("tour.in","r",stdin);
freopen("tour.out","w",stdout);
char city[100][16],s1[16],s2[16];
int i,j,k,v,n,max,p[100][100],d[100][100];
scanf("%d %d",&n,&v);
for(i=0;i<n;i++)scanf("%s",city[i]);
while(v--){
	scanf("%s %s",s1,s2);
	for(i=0;strcmp(city[i],s1);i++);
	for(j=0;strcmp(city[j],s2);j++);
	p[i][j]=p[j][i]=1;
}
d[0][0]=1;
for(max=i=0;i<n;i++)
	for(j=0;j<i;j++)
	    for(k=0;k<i;k++)
	        if(p[k][i] && (k!=j||!k) && d[k][j]+1>d[i][j] && d[k][j]){
				d[j][i]=d[i][j]=d[k][j]+1;
			}
for(i=0;i<n-1;i++)
	if(p[i][n-1] && d[i][n-1]>max)max=d[i][n-1];
printf("%d\n",max<1?1:max);
}
