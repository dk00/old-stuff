#include<stdio.h>
#include<stdlib.h>
struct pos{
	int x,y;
	void get(){scanf("%d %d",&x,&y);x--,y--;}
}r[120],g[120],u,ta[250];
struct Q{
	int x,y,d,s;
}q[2][100000],q2[100000];
int n,m,num,max,map[100][100],tmp1[100][100],tmp2[100][100];
void go(int to[100][100],int x,int y,int d){
	int i,j,s,p;
	for(i=0;i<n;i++)
		for(j=0;j<m;j++)
			tmp1[i][j]=tmp2[i][j]=1;
	q[0][0]=(Q){x,y,d,0};
	for(i=1,j=p=0;i;i=j,j=0,p=!p)
		while(i--){
			x=q[p][i].x,y=q[p][i].y,d=q[p][i].d,s=q[p][i].s;
			to[x][y]<?=s;
			tmp1[x][y]=0;
			if(x && tmp1[x-1][y]){
				if(map[x][y]*d<=map[x-1][y]*d){
					tmp1[x-1][y]=0;
					q[p][i++]=(Q){x-1,y,d,s};
				}
				else if(tmp2[x-1][y]){
					q[!p][j++]=(Q){x-1,y,-d,s+1};
					tmp2[x-1][y]=0;
				}
			}
			if(y && tmp1[x][y-1]){
				if(map[x][y]*d<=map[x][y-1]*d){
					tmp1[x][y-1]=0;
					q[p][i++]=(Q){x,y-1,d,s};
				}
				else if(tmp2[x][y-1]){
					q[!p][j++]=(Q){x,y-1,-d,s+1};
					tmp2[x][y-1]=0;
				}
			}
			if(x+1<n && tmp1[x+1][y]){
				if(map[x][y]*d<=map[x+1][y]*d){
					tmp1[x+1][y]=0;
					q[p][i++]=(Q){x+1,y,d,s};
				}
				else if(tmp2[x+1][y]){
					q[!p][j++]=(Q){x+1,y,-d,s+1};
					tmp2[x+1][y]=0;
				}
			}
			if(y+1<m && tmp1[x][y+1]){
				if(map[x][y]*d<=map[x][y+1]*d){
					tmp1[x][y+1]=0;
					q[p][i++]=(Q){x,y+1,d,s};
				}
				else if(tmp2[x][y+1]){
					q[!p][j++]=(Q){x,y+1,-d,s+1};
					tmp2[x][y+1]=0;
				}
			}
		}
}
int sink,use[300],o[300][300],c[300][300],step[100][100][100];
int findpath(int v){
	use[v]=0;
	if(v==sink)return 1;
	for(int i=1;i<=sink;i++)
		if(use[i] && c[v][i]){
			c[v][i]--;
			if(findpath(i)){
				c[i][v]++;
				return 1;
			}
			c[v][i]++;
		}
	return 0;
}
int flow(){
	int i,j,f=0;
	while(1){
		for(i=0;i<=sink;i++)use[i]=1;
		if(findpath(0))f++;
		else return f;
	}
	return 0;
}
main(){
	int i,j,k,p,t,tt,magic,cn[100];
	/*freopen("10418.in","r",stdin);
	  freopen("10418.out","w",stdout);*/
	scanf("%d",&tt);
	while(tt--){
		scanf("%d %d %d %d",&n,&m,&k,&t);
		for(i=0;i<k;i++)r[i].get();
		for(i=0;i<k;i++)g[i].get();
		u.get();
		for(i=0;i<t;i++){
			ta[i].get();
			scanf("%d",&cn[i]);
		}
		for(i=0;i<n;i++)
			for(j=0;j<m;j++){
				scanf("%d",&map[i][j]);
				for(p=0;p<k*2;p++)
					step[p][i][j]=100000;
			}
		for(i=0;i<k;i++){
			go(step[i],r[i].x,r[i].y,1);
			/*for(j=0;j<n;j++){
			  for(p=0;p<m;p++)
			  printf("%3d",step[i][j][p]);
			  puts("");
			  }
			  puts("");*/
		}
		for(i=0;i<k;i++){
			go(step[i+k],g[i].x,g[i].y,-1);
			/*for(j=0;j<n;j++){
			  for(p=0;p<m;p++)
			  printf("%3d",step[i+k][j][p]);
			  puts("");
			  }
			  puts("");*/
		}
		sink=2*k+t+1;
		for(i=0;i<=sink;i++)
			for(j=0;j<=sink;j++)
				o[i][j]=0;
		for(i=0;i<k;i++)
			o[0][i+1]=o[0][i+k+1]=1;
		for(i=0;i<t;i++)
			o[2*k+1+i][sink]=cn[i];
		for(magic=0;;magic++){
			for(i=0;i<=sink;i++)
				for(j=0;j<=sink;j++)
					c[i][j]=o[i][j];
			for(i=0;i<k;i++)
				for(j=0;j<t;j++){
					if(step[i][ta[j].x][ta[j].y]<=magic)
						c[i+1][j+2*k+1]=1;
					if(step[i+k][ta[j].x][ta[j].y]<=magic)
						c[i+k+1][j+2*k+1]=1;
				}
			if(magic+flow()>=2*k)break;
		}
		printf("%d\n",magic);
	}
}

