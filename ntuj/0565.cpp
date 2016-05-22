#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=99;
struct node{
    int l,r;
}s[99];
int n,m,q[N],f[N];
void build()
{
	char tmp[99];
	scanf("%s",tmp);
	int i,j;
	for(i=j=0;tmp[i];i++){
		int &c=tmp[i]=='0'?s[j].l:s[j].r;
		if(!c){
			c=n++;
			s[c].l=s[c].r=0;
		}
		j=c;
	}
}
int go(int i,int k,int rem,int sum)
{
	if(s[q[i]].l && s[q[i]].r){
		f[q[i]]=f[s[q[i]].l]+f[s[q[i]].r];
		if(!q[i])return f[q[i]]==100;
        if(k>f[q[i]])return 0;
		return go(i+1,k>?f[q[i]],rem,sum);
	}
	if(i>=m)return 1;
	int t;
	for(t=0;k*rem<=sum;k++){
		f[q[i]]=k;
		t+=go(i+1,k,rem-1,sum-k);
	}
	return t;
}
main()
{
    int i,k,C=1;
	while(scanf("%d",&k)==1 && k){
		n=1;
		s[0].l=s[0].r=0;
		for(m=0;m<k;m++)build();
		queue<int> Q;
		m=0,Q.push(0);
		while(!Q.empty()){
			q[m++]=i=Q.front(),Q.pop();
			if(s[i].l && s[i].r)
				Q.push(s[i].r),Q.push(s[i].l);
		}
		reverse(q,q+m);
		printf("Case %d: %d\n",C++,go(0,1,k,100));
	}
}
