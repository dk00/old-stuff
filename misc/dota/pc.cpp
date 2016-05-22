#include<map>
#include<cstdio>
#include<vector>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=20000;
int n,h0;
map<string,int> h;
char x[N][4][5];

void print(char st[4][5])
{
	for(int i=0;i<4;i++)
		st[i][4]=0,puts(st[i]);
}
int num(char stat[4][5])
{
	string tmp="";
	int i;
	for(i=0;i<4;i++)
		stat[i][4]=0,tmp+=stat[i];
	int &j=h[tmp];
	if(!j)
	{
		for(int i=0;i<4;i++)
			for(int j=0;j<5;j++)
				x[h0][i][j]=stat[i][j];
		j=++h0;
	}
	return j;
}
const int dx[]={1,1,-1,-1,2,2,-2,-2},dy[]={2,-2,2,-2,1,-1,1,-1};
char putL(char st[4][5],int x,int y,int d,char v)
{
	if(st[x][y]=='.')st[x][y]=v;
	else return 0;
	if(st[x+dx[d]][y]=='.')st[x+dx[d]][y]=v;
	else return 0;
	if(st[x][y+dy[d]]=='.')st[x][y+dy[d]]=v;
	else return 0;
	if(dx[d]==2 || dx[d]==-2)
	{
		if(st[x+dx[d]/2][y]=='.')st[x+dx[d]/2][y]=v;
		else return 0;
	}		
	else
	{
		if(st[x][y+dy[d]/2]=='.')st[x][y+dy[d]/2]=v;
		else return 0;
	}
	return 1;
}
void rev(char st[4][5])
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(st[i][j]=='#')st[i][j]='*';
			else if(st[i][j]=='*')st[i][j]='#';
}

inline char val(int x,int y){return x>=0 && x<4 && y>=0 && y<4;}

struct pt
{
	int x,y;
	bool operator<(pt a)const
	{
		if(x!=a.x)return x<a.x;
		return y<a.y;
	}
	bool operator!=(pt a)const
	{
		return(x!=a.x || y!=a.y);
	}
}tmp_ed[1600000];
int m;
void expand(char st[4][5])
{
	int i,j,k,n=0,s[128],t[128];
	char ne[4][5];
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			for(k=0;k<8;k++)
			{
				memcpy(ne,st,sizeof(ne));
				if(val(i+dx[k],j+dy[k]) && putL(ne,i,j,k,'#'))
				{
					s[n]=num(ne);
					rev(ne);
					t[n++]=num(ne);
				}
			}
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(i!=j)tmp_ed[m++]=(pt){s[i],t[j]};
}

void init()
{
	int i,j,k,z;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			for(k=0;k<8;k++)
				if(val(i+dx[k],j+dy[k]))
				{
					char st[4][5];
					memset(st,'.',sizeof(st));
					putL(st,i,j,k,'*');

					for(int i=0;i<4;i++)
						for(int j=0;j<4;j++)
							if(st[i][j]=='.')
								for(int k=0;k<4;k++)
									for(int l=0;l<4;l++)
										if((k>i || (k==i && l>j)) && st[k][l]=='.')
										{
											st[i][j]=st[k][l]='x';
											//z=num(st);
											expand(st);
											st[i][j]=st[k][l]='.';
										}
				}
}

vector<int> c[N],r[N];

int gen_st(char st[4][5],int tmp[])
{
	int i,j,x1=-1,x2,y1,y2,n=0;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(st[i][j]=='x')
			{
				if(x1>=0)x2=i,y2=j;
				else x1=i,y1=j;
			}
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(st[i][j]=='.')
			{
				swap(st[i][j],st[x1][y1]);
				tmp[n++]=num(st);
				swap(st[i][j],st[x1][y1]);
				swap(st[i][j],st[x2][y2]);
				tmp[n++]=num(st);
				swap(st[i][j],st[x2][y2]);
			}
	return n;
}

void build_ed()
{
	int i,j,k,tmp[99];
	for(i=m=0;i<=h0;i++)
	{
		for(j=0;j<c[i].size();j++)
		{
			k=gen_st(x[i],tmp);
			while(k--)
				tmp_ed[m++]=(pt){i,tmp[k]};
		}		
	}
}

void add_ed()
{
	pt *s=tmp_ed;
	sort(s,s+m);
	int i;
	for(i=0;i<m;i++)
		if(!i || s[i]!=s[i-1])
		{		
			c[s[i].x].push_back(s[i].y);
		}
}

/* by kelvin */

#define LOSE 0
#define WIN 1
#define DRAW 2

char mes[3][99]={"No winning move\nLosing","","No winning move\nLosing"};
int ord,Order[N];
char Res[N];
int After[N];
bool Visited[N];

int sn,Stack[N];

void DFS_Topo(int v)
{
  int i;
  Visited[v]=1;
  for(i=0;i<c[v].size();i++)
    if(!Visited[c[v][i]]) DFS_Topo(c[v][i]);
  Order[ord++]=v;
}

inline void Topo(void)
{
  int i;
  memset(Visited,0,sizeof(Visited));
  ord=0;
  for(i=0;i<n;i++)
    if(!Visited[i]) DFS_Topo(i);
}

inline void Determine(int v)
{
  int i;
  for(i=0;i<c[v].size();i++)
	  if(!Visited[c[v][i]]||Res[c[v][i]]==DRAW) break;
	if(i==c[v].size()) Res[v]=LOSE;
	else Res[v]=DRAW;
	Visited[v]=1;
}

inline void Solve(void)
{
  int o,v,i;
  Topo();
  memset(Visited,0,sizeof(Visited));
  for(o=0;o<n;o++) {
	  v=Order[o];
	  if(Visited[v]) continue;
	  Determine(v);
	  if(Res[v]==LOSE) {
		  for(i=0;i<r[v].size();i++) {
				Res[r[v][i]]=WIN;
				After[r[v][i]]=v;
				Visited[r[v][i]]=1;
			}
		}
	}
}

/* end of by kelvin */

main()
{
	init();
	add_ed();
	build_ed();
	add_ed();
	int i,j,T,start;
	for(i=0;i<n;i++)
		for(j=0;j<c[i].size();j++)
			r[c[i][j]].push_back(i);
	n=h0+1;
	Solve();
	scanf("%d",&T);
	char tmp[4][5];
	while(T--)
	{
		for(i=0;i<4;i++)
			scanf("%s",tmp[i]);
		rev(tmp);
		j=num(tmp);
		if(Res[j]!=1)
			puts(mes[Res[j]]);
		else
		{
			print(x[After[j]]);
		}
	}
}
