#include<cstdio>
#include <algorithm>
#include <string.h>
const int N=999;
const int MAXT=505;
struct pt{
    int s,t;
    bool operator<(pt a)const{
	if(s!=a.s)return s<a.s;
	return t<a.t;
    }
}s[N];
int n,C,t;
int len[N];
//int M[N];
int M[N][MAXT];
main()
{
    int i,j,k,q,max;
    freopen("pc.in","r",stdin);
    while(scanf("%d %d %d",&n,&C,&t)==3 && n){
	for(i=0;i<n;i++)
	{
	    scanf("%d %d",&s[i].s,&s[i].t);
	    if(s[i].s+t>s[i].t)i--,n--;
	}
	std::sort(s,s+n);
	for(i=0;i<n;i++){
	    for(j=0;i-j-1>=0 && j+1<C && s[i].s+t<=s[j+1].t;j++);
	    len[i]=j+1;
//	    printf("%d ",len[i]);
	}
//	puts("");
	memset(M,0,sizeof(M));
	for(i=0;i<n;i++) {
	    for(j=s[i].s;j+t<=s[i].t;j++) {
		for(k=1;k<=C&&i-k>=0&&j+t<=s[i-k].t;k++);
		if(k+(j?M[i-k+1][j-1]:0)>M[i+1][j+t]) M[j+t]=k+(j?M[j-1]:0);
	    }
	    for(j=0;j<MAXT-1;j++) {
		M[j]=
	    }
	}
/*	for(i=0;i<n;i++) {
	    M[i]=1;
	    if(len[i]>M[i]) M[i]=len[i];
	    for(j=i-len[i];j>=0&&s[j].s+t>s[i].s;j--);
	    for(;j>=0;j--) {
		q=len[i]+M[j];
		if(q>M[i]) M[i]=q;
	    }
	    if(M[i]>max) max=M[i];
	}*/
	printf("%d\n",max);
    }
}
