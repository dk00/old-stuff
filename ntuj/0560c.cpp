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
struct what{
    int end;
    vector<tran> c;
    what& operator=(const char z[]){
	int i,j,n;
	n=strlen(z);
	c.resize(n+1);
	for(i=0;i<n;i++)
	    c[i][z[i]-'a']=i+1;
	for(j=0;j<26;j++)
	    c[i][j]=i;
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
	vector<int> ds,dt;
	ds.resize(c.n,Max+1);
	dt.resize(c.n,Max+1);
	queue<int> Q;
	Q.push(0);
	while(!Q.empty()){
	    
	}
	return *this;
    }
};
int main(){
    while(scanf("%d %d",&n,&m)==2 n+m){
	for(i=0;i<m;i++){
	    scanf("%s",tmp);
	    s[0]=tmp;
	    if(i)s[0]+=s[i];
	    s[0]--;
	}

    }
}
