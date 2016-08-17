#include<stack>
#include<cstdio>
using namespace std;

struct pos{
	int x,y,d;
	void get(){
		scanf("%d %d",&x,&y);x--,y--;
	}
	pos operator+(pos a){
		return (pos){x+a.x,y+a.y};
	}
};

const int Inf=99999,Maxn=101,Maxm=101,Maxk=51,Maxt=101;
const pos ds[]={{1,0},{0,1},{-1,0},{0,-1}};
int n,m,hi[Maxn][Maxm],num[Maxk*2][Maxt];

inline bool valid(pos p){
	return (p.x>=0 && p.x<n && p.y>=0 && p.y<m);
}

//Calculate how many color changes it needs to go from one position to others
//Input: postion x,y, direction d(1:up, -1:down)
//Output: num[Maxn][Maxm](# color change)
void go(int num[Maxn][Maxm],int x,int y,int d)
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			num[i][j]=Inf;
	stack<pos> st[2];
	pos cur={x,y,d};
	st[0].push(cur);
	for(int round=0;!st[0].empty() || !st[1].empty();round=1-round){
		stack<pos> &st0=st[round],&st1=st[1-round];
		while(!st0.empty()){
			cur=st0.top();
			st0.pop();
			for(i=0;i<4;i++){
				pos next=cur+ds[i];
				if(!valid(next) || num[next.x][next.y]<Inf)
					continue;
				if((hi[cur.x][cur.y]-hi[next.x][next.y])*cur.d>0){
					num[next.x][next.y]=num[cur.x][cur.y];
					st0.push(next);
				}else if(num[cur.x][cur.y]+1<num[next.x][next.y]){
					next.d*=-1;
					num[next.x][next.y]=num[cur.x][cur.y]+1;
					st1.push(next);
				}
			}
		}
	}
}


const int Nnode=Maxk*2+Maxt+3;
int sink,used[Nnode],ori[Nnode][Nnode],cap[Nnode][Nnode];

//find an augmenting path, returns 1 if there is one, returns 0 otherwise
int findpath(int v)
{
	if(used[v])return 0;
	used[v]=1;
	if(v==sink)return 1;
	for(int i=1;i<=sink;i++)
		if(cap[v][i]-- && findpath(i))
		{
			cap[i][v]++;
			return 1;
		}
		else
			cap[v][i]++;
	return 0;
}

//Calculate max-flow
int flow(){
	int i,f=0;
	while(1){
		for(i=0;i<=sink;i++)used[i]=0;
		if(findpath(0))f++;
		else return f;
	}
	return 0;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--){
		int i,j,k,t,magic;
		pos spos[Maxk*2+1],goal[Maxt];

		scanf("%d %d %d %d",&n,&m,&k,&t);
		for(i=0;i<=2*k+1;i++)
			scanf("%d %d",&spos[i].x,&spos[i].y);
		sink=2*k+t+1;
		for(i=0;i<=sink;i++)
			for(j=0;j<=sink;j++)
				ori[i][j]=0;
		for(i=1;i<=2*k;i++)
			ori[0][i]=1;
		for(i=0;i<t;i++){
			goal[i].get();
			scanf("%d",&ori[2*k+1+i][sink]);
		}
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				scanf("%d",&hi[i][j]);

		for(i=0;i<2*k;i++)
		{
			int tmp[Maxn][Maxm];
			go(tmp,spos[i].x,spos[i].y,i>=k?1:-1);
			for(j=0;j<t;j++)
				num[i][j]=tmp[goal[j].x][goal[j].y];
		}

		for(magic=0;;magic++){
			for(i=0;i<=sink;i++)
				for(j=0;j<=sink;j++)
					cap[i][j]=ori[i][j];
			for(i=0;i<2*k;i++)
				for(j=0;j<t;j++)
					if(num[i][j]<=magic)
						cap[i+1][j+2*k+1]=1;
			if(magic+flow()>=2*k)break;
		}
		printf("%d\n",magic);
	}
	return 0;
}

