#include<set>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=100005,M=10001,inf=2147483647;
struct pt{
    int x,y;
    bool operator<(pt a)const{
        return x<a.x;
    }
};
struct pl{int h,l,ne,ch;}s[N];
int n,m,h[M],w[M],t[N],a[M];
vector<pt> c[N];
int find(int s[],int n,int x)
{
    int i,j,k;
    for(i=0,j=n-1;i<=j;){
        k=(i+j)/2;
        if(s[k]>x)j=k-1;
        else if(k+1<n && s[k+1]<=x)i=k+1;
        else return k;
    }
}
/*
<------------->
        <--->
  <>  <>  <->
*/
void build(int i)
{
    printf("%d %d\n",i,s[i].l);
    int j,p;
    s[i].ne=s[i].ch=0;
    for(j=1;j<s[i].l;){
        printf(" %d %d %d\n",j,s[i+j].l,i);
        if(s[i+j].l){
            build(i+j);
            if(j)s[p].ne=i+j;
            else s[i].ch=i+j;
            p=i+j;
            j+=s[i+j].l;
        }
        else j++;
    }
}
void print(int v)
{
    putchar('[');
    printf("%d",v);
    if(s[v].ch)print(s[v].ch);
    putchar(']');
    if(s[v].ne)print(s[v].ne);
}
void preproc()
{
    int i,j;
    copy(h,h+m,t+1);
    sort(t,t+m+1);
    for(i=0,j=1;i<m+1;i++)
        if(t[i]!=t[j-1])t[j++]=t[i];
    for(i=0;i<m;i++){
        h[i]=find(t,m+1,h[i]);
        c[w[i]].push_back((pt){h[i],i});
    }
    for(i=1;i<n;i++)
        if(c[i].size())sort(c[i].begin(),c[i].end());
    for(i=1;i<n;i++)
        s[i].h=find(t,m+1,s[i].h);
	for(i=1,j=0;i<n;i++){
		while(j>0 && s[i].h<s[t[j-1]].h)
			s[t[--j]].l=i-t[j];
		if(!j || s[i].h>s[t[j-1]].h)t[j++]=i;
	}
	while(j>0)
		s[t[--j]].l=i-t[j];
    for(i=1;i<n;i++)
        printf("%d ",s[i].h);
    puts("");
    for(i=1;i<n;i++)
        printf("%d ",s[i].l);
    puts("");
	build(1);
	print(1);puts("");
}
main()
{
	int i;
	while(scanf("%d %d",&n,&m)==2){
		for(i=2,n+=2;i<n;i++)
			scanf("%d",&s[i].h);
		for(i=0;i<m;i++)
			scanf("%d %d",w+i,h+i);
		preproc();
	}
}
