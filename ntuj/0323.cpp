#include<stdio.h>
#define BIG 1000000

int map[500][500];
int dx[10][2];
int node[10000][2];
int x1[5000],x2[5000],y1[5000],y2[5000];

int main(){
	int M,N,n,t=0,ptr;
	int i,j,k,a,b,c,tri,x,y;
	dx[0][0]=1,dx[0][1]=0;
	dx[1][0]=1,dx[1][1]=1;
	dx[2][0]=0,dx[2][1]=1;
	dx[3][0]=-1,dx[3][1]=1;
	dx[4][0]=-1,dx[4][1]=0;
	dx[5][0]=-1,dx[5][1]=-1;
	dx[6][0]=0,dx[6][1]=-1;
	dx[7][0]=1,dx[7][1]=-1;
	dx[8][0]=1,dx[8][1]=0;
	dx[9][0]=1,dx[9][1]=1;
	dx[10][0]=0,dx[10][1]=1;
	while(scanf("%d %d %d",&M,&N,&n)!=EOF){
		tri=0;
		t++;
		for(i=0;i<=4*M+8;i++){
			for(j=0;j<=4*N+8;j++)
				map[i][j]=t;
		}
		for(i=0;i<n;i++)
			scanf("%d %d %d %d",x1+i,y1+i,x2+i,y2+i);
		x1[n]=0,y1[n]=0,x2[n]=M,y2[n]=0;
		x1[n+1]=0,y1[n+1]=0,x2[n+1]=0,y2[n+1]=N;
		x1[n+2]=0,y1[n+2]=N,x2[n+2]=M,y2[n+2]=N;
		x1[n+3]=M,y1[n+3]=0,x2[n+3]=M,y2[n+3]=N;
		for(i=0;i<n+4;i++){
			x1[i]=4*x1[i]+4;
			x2[i]=4*x2[i]+4;
			y1[i]=4*y1[i]+4;
			y2[i]=4*y2[i]+4;
			if(x1[i]<x2[i] && y1[i]==y2[i])k=0;
			if(x1[i]<x2[i] && y1[i]<y2[i])k=1;
			if(x1[i]==x2[i] && y1[i]<y2[i])k=2;
			if(x1[i]>x2[i] && y1[i]<y2[i])k=3;
			if(x1[i]>x2[i] && y1[i]==y2[i])k=4;
			if(x1[i]>x2[i] && y1[i]>y2[i])k=5;
			if(x1[i]==x2[i] && y1[i]>y2[i])k=6;
			if(x1[i]<x2[i] && y1[i]>y2[i])k=7;
			for(x=x1[i],y=y1[i];x!=x2[i] || y!=y2[i];x+=dx[k][0],y+=dx[k][1])
				map[x][y]+=BIG;
			map[x][y]+=BIG;
		}
		ptr=0;
		/*for(i=4;i<=4*M+4;i++){
			for(j=4;j<=4*M+4;j++)
				printf("%d ",map[i][j]/BIG);
			puts("");
		}*/
		for(i=4;i<=4*M+4;i++){
			for(j=4;j<=4*N+4;j++){
				if(map[i][j]>2*BIG){
					//printf("%d %d\n",i,j);
					for(k=0;k<8;k++){
						if(map[i+dx[k][0]][j+dx[k][1]]>BIG){
							if(k%2==0){
								for(a=4;map[i+a*dx[k][0]][j+a*dx[k][1]]==BIG+t;a+=4);
								if(map[i+dx[k+2][0]][j+dx[k+2][1]]!=BIG+t)b=1;
								else{
									for(b=4;map[i+b*dx[k+2][0]][j+b*dx[k+2][1]]==BIG+t;b+=4);
								}
								if(a==b){
									if(map[i+a*dx[k][0]+dx[k+3][0]][j+a*dx[k][1]+dx[k+3][1]]!=BIG+t)
										c=1;
									else{
										for(c=2;map[i+a*dx[k][0]+c*dx[k+3][0]][j+a*dx[k][1]+c*dx[k+3][1]]==BIG+t;c+=2);
									}
									if(a*dx[k][0]+c*dx[k+3][0]==b*dx[k+2][0] && a*dx[k][1]+c*dx[k+3][1]==b*dx[k+2][1]){
										tri++;
									}
								}
							}
							else{
								for(a=2;map[i+a*dx[k][0]][j+a*dx[k][1]]==BIG+t;a+=2);
								if(map[i+dx[k+2][0]][j+dx[k+2][1]]!=BIG+t)b=1;
								else{
									for(b=2;map[i+b*dx[k+2][0]][j+b*dx[k+2][1]]==BIG+t;b+=2);
								}
								if(a==b){
									if(map[i+a*dx[k][0]+dx[k+3][0]][j+a*dx[k][1]+dx[k+3][1]]!=BIG+t)
										c=1;
									else{
										for(c=4;map[i+a*dx[k][0]+c*dx[k+3][0]][j+a*dx[k][1]+c*dx[k+3][1]]==BIG+t;c+=4);
									}
									if(a*dx[k][0]+c*dx[k+3][0]==b*dx[k+2][0] && a*dx[k][1]+c*dx[k+3][1]==b*dx[k+2][1]){
										tri++;
									}
								}
							}
						}
					}
				}
			}
		}
		printf("%d\n",tri);
	}
	return 0;
}
