#include<queue>
#include<iostream>
using namespace std;
main(){
	priority_queue<int> test;
	int i,a,b,n,cost;
	while(cin>>n && n){
		cost=0;
		while(n--){
			cin>>i;
			test.push(-i);
		}
		while(test.size()>1){
			a=-test.top();
			test.pop();
			b=-test.top();
			test.pop();
			i=a+b;
			cost+=i;
			test.push(-i);
		}
		test.pop();
		cout<<cost<<'\n';
	}
}

