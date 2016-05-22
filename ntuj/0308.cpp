#include<stdio.h>

int v[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

int poly[50][2],ver[50][2],n;

bool inside(int x, int y, int r){ //radius=r/1000
	int i,turn=0;
	for(i=1;i<n;i++){
		if(ver[i][0]>=x && ver[i-1][0]>=x){
			if(ver[i][1]>=y && ver[i-1][1]<=y)
				turn++;
			else if(ver[i][1]<=y && ver[i-1][1]>=y)
				turn--;
		}
	}
	if(ver[0][0]>=x && ver[n-1][0]>=x){
		if(ver[0][1]>=y && ver[n-1][1]<=y)
			turn++;
		else if(ver[0][1]<=y && ver[n-1][1]>=y)
			turn--;
	}
	if(turn!=1)
		return false;
	for(i=0;i<n;i++){
		if((ver[i][0]-x)*(ver[i][0]-x)+(ver[i][1]-y)*(ver[i][1]-y)*1000000ll<(long long)r*r)
			return false;
	}
	for(i=0;i<n;i++){
		if(poly[i][1]%2==0){
			if( (ver[i][0]-x)*(ver[(i+1)%n][0]-x)<0 ){
				if( (ver[i][1]-y)*(ver[i][1]-y)*1000000ll<((long long)r)*r)
					return false;
			}
		}
	}
	return true;
}

int main(){
	int i;
	char c;
	while(1){
		scanf("%d",&n);
		if(n==0)
			break;
		for(i=0;i<n;i++){
			scanf("%d %c",&poly[i][0],&c);
			if(c=='R')
				poly[i][1]=0;
			else if(c=='U')
				poly[i][1]=1;
			else if(c=='L')
				poly[i][1]=2;
			else
				poly[i][1]=3;
		}
		ver[0][0]=ver[0][1]=0;
		for(i=1;i<n;i++){
			ver[i][0]=ver[i-1][0]+poly[i-1][0]*v[poly[i-1][1]][0];
			ver[i][1]=ver[i-1][1]+poly[i-1][0]*v[poly[i-1][1]][1];
		}
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				if(j==i)
					continue;
				for(k=0;k<n;k++){
					if((k-i)*(k-j)==0)
						continue;
					
				}
			}
		}
	}
}
