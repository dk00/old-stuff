#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
int n;
int match_left[600];	//left point i match right point match_left[i])
int match_right[600];
int weight[600][600];
int spfa(){
	enum{TARGET=601,MIN=-10000000};
	int l[601],last[601];
	queue<int> que;
	bool inqueue[600]={};
	for(int i=0;i<n;++i)
		if(match_left[i]==-1){
			que.push(i);
			inqueue[i]=true;
			l[i]=0;
		}else{
			l[i]=MIN;
		}
	l[TARGET]=MIN;
	while(!que.empty()){
		int x=que.front();
//		cout<<x<<endl;
		que.pop();
		inqueue[x]=false;
		for(int i=0;i<n;++i){
			int y=i;
			if(match_right[y]==-1){
				if(l[x]+weight[x][y]>l[TARGET]){
					l[TARGET]=l[x]+weight[x][y];
					last[y]=x;
					last[TARGET]=y;
				}
			}else if(match_right[y]!=x){
				if(l[x]+weight[x][y]-weight[match_right[y]][y]>l[match_right[y]]){
					l[match_right[y]]=l[x]+weight[x][y]-weight[match_right[y]][y];
					last[y]=x;
					if(!inqueue[match_right[y]]){
						que.push(match_right[y]);
						inqueue[match_right[y]]=true;
					}
				}
			}
		}
	}
	if(l[TARGET]==MIN)
		return 0;
	int t=last[TARGET];
	while(t!=-1){
//		cout<<t<<endl;
		int next_t=match_left[last[t]];
		match_right[t]=last[t];
		match_left[last[t]]=t;
		t=next_t;
	}
//	cout<<"spfa ok"<<endl;
	return l[TARGET];
}
int main(){
	ios_base::sync_with_stdio(false);
    freopen("pc.in","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
		for(int i=0;i<n;++i){
			int t1,t2,w;
            for(int j=0;j<n;++j){
                scanf("%d%d%d",&t1,&t2,&w);
				weight[t1-1][t2-n-1]=w;
            }
		}
		memset(match_left,-1,sizeof(match_left));
		memset(match_right,-1,sizeof(match_right));
		int ans=0;
		for(int i=0;i<n;++i){
			int t;
			if(!(t=spfa())){
				ans=0;
				break;
			}
			ans+=t;
		}
        printf("%d\n",ans);
        scanf("%*d");
	}
	return  0;
}
