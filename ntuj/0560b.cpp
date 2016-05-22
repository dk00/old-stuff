#include<map>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
struct tran{
    int s[26];
    tran(){
	for(int i=0;i<26;i++)s[i]=0;
    }
    int& operator[](int x){return s[x];}
};
int Max,End;
struct automaton{
    int end;
    vector<tran> c;
    automaton(){
	end=0;
	c.resize(1);
    }
    automaton& operator=(const char t[]){
        c.clear();
        c.resize(strlen(t)+1);
        int i,j;
        for(i=0;t[i];i++)
	    c[i][t[i]-'a']=i+1;
        for(j=0;j<26;j++)
            c[i][j]=i;
	end=i;
	return *this;
    }
    automaton& operator+=(automaton& m){
        queue<int> Q;
        map<int,int> H;
	vector<tran> c0=c;
	vector<tran>& c1=m.c;
	int i,j,k,x,z,n=c.size();
        for(i=0;i<n;i++)
            Q.push(i),H[i]=i;
        while(!Q.empty()){
            x=Q.front(),Q.pop();
            j=x/n,i=x%n,x=H[x];
            for(k=0;k<26;k++){
                if(!H.count(z=c0[i][k]+n*c1[j][k])){
                    Q.push(z);
                    H[z]=c[x][k]=c.size();
                    c.resize(c[x][k]+1);
                }
                c[x][k]=H[z];
            }
        }
	printf("%d",c.size());
	end=H[end+n*(c1.size()-1)];
	return *this;
    }
    automaton& operator--(int){
	vector<int> d0,d1,t;
	vector<vector<int> > rev;
	t.resize(c.size(),0);
	d0.resize(c.size(),Max+1);
	d1.resize(c.size(),Max+1);
	rev.resize(c.size());
	int i,j,k;
	for(i=0;i<c.size();i++)
	    for(j=0;j<26;j++)
		if(c[i][j]!=i)
		    rev[c[i][j]].push_back(i);
	queue<int> Q;
	d0[0]=0;
	Q.push(0);
	while(!Q.empty()){
	    i=Q.front(),Q.pop();
	    for(j=0;j<26;j++)
		if(d0[i]+1<d0[c[i][j]]){
		    d0[c[i][j]]=d0[i]+1;
		    Q.push(c[i][j]);
		}
	}
	d1[end]=0;
	Q.push(end);
	while(!Q.empty()){
	    i=Q.front(),Q.pop();
	    for(j=0;j<rev[i].size();j++)
		if(d1[i]+1<d1[rev[i][j]]){
		    d1[rev[i][j]]=d1[i]+1;
		    Q.push(rev[i][j]);
		}
	}
	for(i=j=0;i<c.size();i++){
	    if(!i || i==end || d0[i]+d1[i]<=Max){
		t[i]=j;
		c[j++]=c[i];
	    }
	}
	end=t[end];
	c.resize(j);
	for(i=0;i<c.size();i++)
	    for(k=0;k<26;k++)
		c[i][k]=t[c[i][k]];
	printf(" => %d\n",j);
	return *this;
    }
};
long long *num[26];
bool go(vector<tran>& c,int d,int v){
    if(!num[d][v])return false;
    if(d==Max){
	if(v==End)
	   return true;
	num[d][v]=0;
	return false;
    }
    bool f=false;
    for(int i=0;i<26;i++)
	if(go(c,d+1,c[v][i]))f=true;
    if(!f)num[d][v]=0;
    return f;
}
char path[26];
void print(vector<tran>& c,int d,int v)
{
    if(d==Max){
	puts(path);
	return;
    }
    for(int i=0;i<26;i++){
	path[d]='a'+i;
	if(num[d+1][c[v][i]])
	    print(c,d+1,c[v][i]);
    }
}
main()
{
    int i,j,k,n,m,C=1;
    while(scanf("%d %d",&n,&m)==2 && n+m){
	Max=n;
        automaton s[10];
        for(i=0;i<m;i++){
            char tmp[10];
            scanf("%s",tmp);
            s[i]=tmp;
            if(i)s[0]+=s[i];
	    s[0]--;
        }
	vector<tran>& c=s[0].c;
	m=c.size();
	for(i=0;i<=n;i++)
	    num[i]=new long long[m];
	for(i=0;i<m;i++)
	    num[0][i]=0;
	num[0][0]=1;
	for(i=0;i<n;i++){
	    for(j=0;j<m;j++)
		num[i+1][j]=0;
	    for(j=0;j<m;j++)
		for(k=0;k<26;k++)
		    num[i+1][c[j][k]]+=num[i][j];
	}
	End=s[0].end,path[n]=0;
	printf("Case %d: %lld suspects\n",C++,num[i][End]);
	if(num[i][s[0].end]<=51)
	    go(c,0,0),print(c,0,0);
	for(i=0;i<=n;i++)
	    delete num[i];
    }
}
