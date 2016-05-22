#include<iostream>
#include<string>
using namespace std;
int maxv(string s){
	int ret=0;
	for(int i=0;i<s.size();++i)
		if(s[i]-'0'>ret)
			ret = s[i]-'0';
	return ret+1;
}
int tov(string s,int b){
	int ret=0;
	for(int i=0;i<s.size();++i){
		ret*=b;
		ret+=s[i]-'0';
	}
	return ret;
}
int main(void){
	int t,x,y,v,u;
	string a,b;
	for(cin>>t;t>0;--t){
		cin>>a>>b;
		v=maxv(a);
		u=maxv(b);
		x=tov(a,v);
		y=tov(b,u);
		cout<<x+y<<endl;
	}
	return 0;
}
