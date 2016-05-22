#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
#define MaxN 6
int n,m;
struct Point{
	int x,y;
}p[MaxN];
int r[MaxN];
vector< Point > d[MaxN];
int oArea[1801][901],ansMax;
short int mark[1801][901],times;
int used[MaxN];
inline int cross( const Point &p0, const Point &p1,const Point &p2)
{
	return (p1.x-p0.x)*(p2.y-p0.y) - (p2.x-p0.x)*(p1.y-p0.y);
}
inline int sgn( int x ){
	return x<0?-1:(x>0?1:0);
}
void fnInit()
{
	int i,dx,dy;
	Point tmp;
	for( i=0;i<n;i++){
		cin >> r[i];
		d[i].clear();
		for( dx=-r[i];dx<=r[i];dx++)
			for( dy=-r[i];dy<=r[i];dy++)
				if( dx*dx+dy*dy == r[i]*r[i] ){
					tmp.x = dx;
					tmp.y = dy;
					d[i].push_back( tmp );
				}
	}
	if( n&1 ){
		r[n] = 0;
		d[n].clear();
		tmp.x = tmp.y = 0;
		d[n].push_back( tmp );
		++n;
	}
	m = (n>>1);
}
int sum=0;
void fnGo( int level , int curArea )
{
    sum++;
	if( level==m ){
		int x=p[level].x , y = p[level].y;
		if( mark[x+900][y]==times ) oArea[x+900][y] = max( oArea[x+900][y] , curArea );
		else{
			mark[x+900][y] = times;
			oArea[x+900][y] = curArea;
		}
		return ;		
	}
	for(int i =0;i<n;i++){
		if( used[i]!=1 ) continue;
		used[i] = 2;
		for( int j=0;j<d[i].size();j++){
			p[level+1].x = p[level].x+d[i][j].x;
			p[level+1].y = p[level].y+d[i][j].y;
			if( p[level+1].y<0 ) continue;
			if( level==0 && (p[1].x<0||p[1].x>p[1].y )) continue;
			if( level==2 && sgn(cross(p[0],p[1],p[2]))*sgn(cross(p[1],p[2],p[3]))<0) continue;
			int delta = cross( p[0] , p[level] , p[level+1] );
			if( delta<0 ) continue;
			fnGo( level+1,curArea+delta);
		}
		used[i] = 1;
	}	
}

void fnGo2( int level , int curArea )
{
    sum++;
	if( level==m ){
		int x = p[level].x , y = p[level].y;
		if( mark[x+900][y]==times ){
			ansMax = max( ansMax , oArea[x+900][y]+curArea );
		}
		return ;		
	}
	for(int i =0;i<n;i++){
		if( used[i]!=0 ) continue;
		used[i] = 2;
		for( int j=0;j<d[i].size();j++){
			p[level+1].x = p[level].x+d[i][j].x;
			p[level+1].y = p[level].y+d[i][j].y;
			if( p[level+1].y<0 ) continue;
			if( level==2 && sgn(cross(p[0],p[1],p[2]))*sgn(cross(p[1],p[2],p[3]))<0) continue;
			int delta = -cross( p[0] , p[level] , p[level+1] );
			if( delta<0 ) continue;
			fnGo2( level+1,curArea+delta);
		}
		used[i] = 0;
	}	
}
void fnSolve( int index , int cntUsed )
{
	if( cntUsed + n-index < m ) return;
	if( cntUsed!=m && index !=n ){
		fnSolve(index+1,cntUsed);	
		used[index] = 1;
		fnSolve(index+1,cntUsed+1);
		used[index] = 0;
	}else{
		if( cntUsed==m ){
			++times;		
			fnGo(0,0);	
			fnGo2(0,0);		
		}	
	}	
}
int main()
{
	int i,j,k;
	while( cin >> n ){
		if( !n ) break;
		fnInit();
		p[0].x = 0;
		p[0].y = 0;		
		ansMax = 0;
		sum=0;
		fnSolve(0,0);
		if( ansMax==0 )
			cout << "-1" << ' '<<sum<<endl;
		else
			cout << (ansMax>>1) << ' '<<sum<<endl;
	}

	return 0;
}

