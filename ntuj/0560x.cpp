#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct tran{
    int t[26];
    tran(){fill(t,t+26,0);}
    int& operator[](int i){
	return t[i];
    }
};
int Max;
void sp(int st,vector<vector<int> >& c,vector<int>& d){
    d.resize(c.size()+1,Max);
    queue<int> Q;
    Q.push(st);
    d[st]=0;
    int i,j;
    while(!Q.empty()){
	i=Q.front(),Q.pop();
	for(j=0;j<c[i].size();j++)
	    if(d[i]+1<d[c[i][j]]){
		d[c[i][j]]=d[i]+1;
		Q.push(c[i][j]);
	    }
    }
}
struct what{
    int end;
    vector<tran> c;
    what& operator=(const char z[]){
	int i,j,k,n;
	n=strlen(z);
	c.resize(n+1);
	for(i=0;i<n;i++)
	    c[i][z[i]-'a']=i+1;
        for(i=1,j=0;i<n;i++){
	    for(k=0;k<26;k++)
		if(c[i][k]==0)
		    c[i][k]=c[j][k];
	    j=c[j][z[i]-'a'];
        }
	for(j=0;j<26;j++)
	    c[n][j]=n;
	end=n;
	return *this;
    }
    what& operator+=(what& x){
	vector<tran> c0=c;
	vector<tran>& c1=x.c;
	c.resize(c0.size()*c1.size());
	unsigned i,j,k,a,b;
	end=c0.size()*c1.size()-1;
	for(i=0;i<c0.size();i++)
	    for(j=0;j<c1.size();j++)
		for(k=0;k<26;k++){
		    a=i+j*c0.size();
		    b=c0[i][k]+c1[j][k]*c0.size();
		    c[a][k]=b;
		}
	return *this;
    }
    what& operator--(int){
	vector<int> ds,dt,t;
	vector<vector<int> > o,r;
	t.resize(c.size(),0);
	o.resize(c.size());
	r.resize(c.size());
	int i,j,k;
	for(i=0;i<c.size();i++){
	    o[i].resize(26);
	    for(j=0;j<26;j++){
		o[i][j]=c[i][j];
		if(c[i][j]!=i)
		    r[c[i][j]].push_back(i);
	    }
	}
	sp(0,o,ds);
	sp(end,r,dt);
	for(i=j=0;i<c.size();i++)
	    if(!i || i==end || ds[i]+dt[i]<=Max){
		t[i]=j;
		c[j++]=c[i];
	    }
	c.resize(j);
	for(i=0;i<j;i++)
	    for(k=0;k<26;k++)
		c[i][k]=t[c[i][k]];
	end=t[end];
	return *this;
    }
};
vector<long long> num[26];
long long go(vector<tran>& c,int d,int v){
    if(num[d][v])
	return max(num[d][v],0ll);
    if(d>=Max){
	num[d][v]=-1;
	return 0;
    }
    for(int i=0;i<26;i++)
	num[d][v]+=go(c,d+1,c[v][i]);
    if(!num[d][v])num[d][v]--;
    return max(num[d][v],0ll);
}
char tmp[99];
void print(vector<tran>& c,int d,int v){
    if(d==Max){
	puts(tmp);
	return;
    }
    for(int i=0;i<26;i++){
	tmp[d]='a'+i;
	if(num[d+1][c[v][i]]>0)
	    print(c,d+1,c[v][i]);
    }
}
int main(){
    int i,n,m,C=1;
    while(scanf("%d %d",&n,&m)==2 && n+m){
	Max=n;
	what s[10];
	s[0]="";
	for(i=0;i<m;i++){
	    scanf("%s",tmp);
	    s[i]=tmp;
	    if(i)s[0]+=s[i];
	    s[0]--;
	}
	vector<tran>& c=s[0].c;
	for(i=0;i<=n;i++){
	    num[i].clear();
	    num[i].resize(c.size(),0);
	}
	num[n][s[0].end]=1;
	printf("Case %d: %lld suspects\n",C++,go(c,0,0));
	if(num[0][0]>0 && num[0][0]<=42)
	    tmp[n]=0,print(c,0,0);
    }
}
