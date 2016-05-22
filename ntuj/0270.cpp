#include<stdio.h>

int polyptr[2510],hei[2510],nov;
int vertex[200100][2];

int anc[2510],child[2510][2510],chptr[2510];

int queue[2510],used[2510],st,ed,up[2510],down[2510];

int rel[2510][2510],rc[2510];

long long area[2510];

int main(){
	int t,i,j,k,n,x1,y1,x2,y2,tmp,ori,tmpx,tmpy;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(i=0;i<=n+2;i++)
			chptr[i]=0;
		polyptr[0]=0;
		for(i=1;i<=n;i++){
			scanf("%d %d",hei+i,&nov);
			polyptr[i]=polyptr[i-1]+nov+1;
			for(j=polyptr[i-1]+1;j<polyptr[i];j++)
				scanf("%d %d",&vertex[j][0],&vertex[j][1]);
			vertex[j][0]=vertex[polyptr[i-1]+1][0];
			vertex[j][1]=vertex[polyptr[i-1]+1][1];
		}
		for(i=1;i<=n;i++){
			area[i]=0;
			for(j=polyptr[i-1]+2;j<polyptr[i]-1;j++){
				x1=vertex[j][0]-vertex[polyptr[i]][0];
				y1=vertex[j][1]-vertex[polyptr[i]][1];
				x2=vertex[j+1][0]-vertex[polyptr[i]][0];
				y2=vertex[j+1][1]-vertex[polyptr[i]][1];
				area[i]+=((long long)x1)*y2-((long long)x2)*y1;
			}
			if(area[i]<0)
				area[i]=-area[i];
		}
		for(i=0;i<=n+2;i++)
			rc[i]=0;
		for(i=1;i<=n;i++){
			ori=0;
			for(j=polyptr[i-1]+1;j<polyptr[i];j++){
				x1=vertex[j][0],y1=vertex[j][1];
				x2=vertex[j+1][0],y2=vertex[j+1][1];
				if( (y1<=0&&y2>0) || (y2<=0&&y1>0) ){
					if(y1>y2)tmp=-1;
					else tmp=1;
					if(y1<0)y1=-y1;
					if(y2<0)y2=-y2;
					if(((long long)x1)*y2+((long long)x2)*y1>0)
						ori+=tmp;
				}
			}
			if(ori!=0)
				rel[n+1][i]=1,rc[n+1]++;
			else
				rel[n+1][i]=0;
		}
		//if(i>n)i=0;
		//child[i][chptr[i]++]=n+1;
		//anc[n+1]=i;
		for(i=1;i<=n;i++){
			ori=0;
			for(j=polyptr[i-1]+1;j<polyptr[i];j++){
				x1=vertex[j][0]-100000,y1=vertex[j][1];
				x2=vertex[j+1][0]-100000,y2=vertex[j+1][1];
				if( (y1<=0&&y2>0) || (y2<=0&&y1>0) ){
					if(y1>y2)tmp=-1;
					else tmp=1;
					if(y1<0)y1=-y1;
					if(y2<0)y2=-y2;
					if(((long long)x1)*y2+((long long)x2)*y1>0)
						ori+=tmp;
				}
			}
			if(ori!=0)
				rel[n+2][i]=1,rc[n+2]++;
			else
				rel[n+2][i]=0;
		}
		//if(i>n)i=0;
		//child[i][chptr[i]++]=n+2;
		//anc[n+2]=i;

		for(k=1;k<=n;k++){
			for(i=1;i<=n;i++){
				if(i==k){
					rel[k][i]=0;
					continue;
				}
				else if(area[k]>=area[i]){
					rel[k][i]=0;
					continue;
				}
				ori=0;
				tmpx=vertex[polyptr[k]][0];
				tmpy=vertex[polyptr[k]][1];
			    y2=vertex[polyptr[i-1]+1][1]-tmpy;
				for(j=polyptr[i-1]+1;j<polyptr[i];j++){
					y1=y2;
					//y1=vertex[j][1]-vertex[polyptr[k]][1];
					y2=vertex[j+1][1]-tmpy;
					if( (y1<=0&&y2>0) || (y2<=0&&y1>0) ){
						x1=vertex[j][0]-tmpx;
						x2=vertex[j+1][0]-tmpx;
						if(x1<=0 && x2<=0)
							continue;
						if(y1>y2)tmp=-1;
						else tmp=1;
						if(y1<0)y1=-y1;
						if(y2>0){
							if(((long long)x1)*y2+((long long)x2)*y1>0)
								ori+=tmp;
						}
						else{
							if(((long long)x2)*y1-((long long)x1)*y2>0)
								ori+=tmp;
						}
					}
				}
				if(ori!=0)
					rel[k][i]=1,rc[k]++;
				else
					rel[k][i]=0;
			}
			//if(i>n)i=0;
			//child[i][chptr[i]++]=k;
			//anc[k]=i;
		}

		st=ed=0;
		for(i=1;i<=n+2;i++){
			if(rc[i]==0){
				queue[ed++]=i;
				anc[i]=0;
				child[0][chptr[0]++]=i;
			}
		}
		while(st<ed){
			tmp=queue[st++];
			if(tmp>n)continue;
			for(i=1;i<=n+2;i++){
				if(rel[i][tmp]==1){
					rc[i]--;
					if(rc[i]==0){
						queue[ed++]=i;
						anc[i]=tmp;
						child[tmp][chptr[tmp]++]=i;
					}
				}
			}
		}
		anc[0]=0;
		st=0,ed=1;
		queue[st]=n+1;
		up[n+1]=down[n+1]=0;
		for(i=0;i<=n+2;i++)used[i]=0;
		used[n+1]=1;
		while(st<ed){
			tmp=queue[st++];
			if(used[anc[tmp]]==0){
				queue[ed++]=anc[tmp];
				used[anc[tmp]]=1;
				up[anc[tmp]]=up[tmp];
				down[anc[tmp]]=down[tmp];
				if(anc[tmp]!=0 && tmp<=n){
					if(hei[anc[tmp]]>hei[tmp])up[anc[tmp]]+=hei[anc[tmp]]-hei[tmp];
					else down[anc[tmp]]-=hei[anc[tmp]]-hei[tmp];
				}
				for(i=0;i<chptr[anc[tmp]];i++){
					j=child[anc[tmp]][i];
					if(used[j]==1)continue;
					queue[ed++]=j;
					used[j]=1;
					up[j]=up[tmp];
					down[j]=down[tmp];
					if(j<=n && tmp<=n){
						if(hei[j]>hei[tmp])up[j]+=hei[j]-hei[tmp];
						else down[j]-=hei[j]-hei[tmp];
					}
				}
			}
			for(i=0;i<chptr[tmp];i++){
				j=child[tmp][i];
				if(used[j]==1)continue;
				queue[ed++]=j;
				used[j]=1;
				up[j]=up[tmp];
				down[j]=down[tmp];
				if(j<=n){
					if(hei[j]>hei[tmp])up[j]+=hei[j]-hei[tmp];
					else down[j]-=hei[j]-hei[tmp];
				}
			}
		}
		//for(i=1;i<=n+2;i++){
		//	for(j=1;j<=n;j++)
		//		printf("%d ",rel[i][j]);
		//	puts("");
		//}
		//puts("");
		//for(i=0;i<=n+2;i++)
		//	printf("%d\n",anc[i]);
		//puts("");
		//for(i=0;i<ed;i++)
		//	printf("%d\n",queue[i]);
		printf("%d %d\n",up[n+2],down[n+2]);
	}
	return 0;
}
