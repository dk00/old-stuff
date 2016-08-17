#include<cstdio>
typedef unsigned long long u64;
const int N=500000;
struct pre
{
	int l,r,u;
	u64 num;
}s[N];
int n,m,sn;
u64 go(char p[])
{
    int i,j;
	for(i=j=0;p[i]!='*';i++){
		j=p[i]=='0'?s[j].l:s[j].r;
		if(!j)break;
	}
	while(p[i]!='*')i++;
	if(i>0 && !j)return 1llu<<(m-i);
	return s[j].num;
}
u64 go(int d,int v)
{
	if(d>=m)return s[v].num=1;
	s[v].num=0;
	u64 ln=s[v].l?go(d+1,s[v].l):1llu<<(m-d-1),rn=s[v].r?go(d+1,s[v].r):1llu<<(m-d-1);
	if(!s[v].l || s[s[v].l].u)s[v].num+=ln;
	if(!s[v].r || s[s[v].r].u)s[v].num+=rn;
	return s[v].num;
}
void go(int &v)
{
    if(v)return;
	v=sn++;
	s[v].u=1,s[v].l=s[v].r=0;
}
void build(char p[])
{
	int i,j;
	for(i=j=0;p[i]!='*';i++){
		int &k=p[i]=='0'?s[j].l:s[j].r;
		go(k);
		j=k;
	}
	s[j].u=0;
}
char tmp[999];
main()
{
	int i,q;
	while(scanf("%d %d",&n,&m)==2 && n+m){
		s[0].l=s[0].r=s[0].u=0;
		for(i=0,sn=1;i<n;i++){
			scanf("%s",tmp);
			build(tmp);
		}
		go(0,0);
		scanf("%d",&q);
		while(q--){
			scanf("%s",tmp);
			if(tmp[0]=='*' && m==64 && sn<2){
                puts("18446744073709551616");
                continue;
            }
			printf("%llu\n",go(tmp));
		}
		puts("");
	}
}
