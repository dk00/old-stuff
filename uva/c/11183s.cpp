#include <iostream>
#include <vector>
#include <map>

#define INF 500000000

using namespace std;

class edge{
	public:
		edge(int a, int b):from(a),dist(b){}
		int from,dist;
};

vector<edge> e[1010];  //directed edge  from  "e[i][k].from"   to   "i"
int sel[1010];
int N;
int ptexist[1010];

int findpte( int x ){
	if( ptexist[x] == -1 ) return x;
	ptexist[x] = findpte( ptexist[x] );
	return ptexist[x];
}


vector<int> *trace( int pos, map<int,int> *done, vector<int> *t, int *visited ){
	int marker = 0 , k;
	vector<int> *j;
	if( visited[pos] == 2 ) return NULL;
	visited[pos] = 1;
	if( done == NULL ){
		marker = 1;
		done = new map<int,int>;
		t = new vector<int>;
	}
	t->push_back( pos );
	if( (*done)[pos] == 1) return t;
	(*done)[pos] = 1;
	if( sel[pos] == -1 ){
		if( marker ){
			delete done;
			delete t;
		}
		visited[pos] = 2;
		return NULL;
	}

	k = findpte( e[pos][ sel[pos] ].from );
	j = trace(k,done,t,visited);
	if( j == NULL ){
		if( marker ){
			delete done;
			delete t;
		}
		visited[pos] = 2;
		return NULL;
	}
	if( marker ) delete done;
	return t;
}



vector<int> *checkloop(){
	int visited[1010];
	int i,k,m;
	vector<int> *j,*ret;

	for(i=1;i<N;i++){
		if( ptexist[i] != -1 ) continue;
		visited[i] = 0;
	}

	for( i=1 ; i<N ; i++ ){
		if( ptexist[i] != -1 ) continue;
		if( visited[i] == 0 ){
			j=trace(i,NULL,NULL,visited);
			if( j != NULL ){
				ret = new vector<int>;
				ret->push_back( (*j)[ j->size()-1 ] );
				for( k = j->size()-2 ; (*j)[k] != (*ret)[0] ; k-- )
					ret->push_back( (*j)[k] );
				delete j;
				return ret;
			}
		}
	}
	return NULL;
}

int contract(vector<int> &loop){
	int i,j,k;
	vector<edge> newnode;

	for( i=0 ; i<loop.size() ; i++){
		if(i)ptexist[loop[i]]=loop[0];
	}

	for( i=0 ; i<loop.size() ; i++ ){
		for( j=0 ; j < e[loop[i]].size() ; j++ ){
			k=findpte(e[loop[i]][j].from);
			if( k == loop[0] )continue;
			newnode.push_back( edge( e[loop[i]][j].from , e[loop[i]][j].dist-e[loop[i]][sel[loop[i]]].dist ));
		}
	}
	e[loop[0]] = newnode;

	return loop[0];
}


int makemst(){	//return weight of mst,-1 indicate disconnected
	int i,j,k,ret = 0;
	vector<int> *loop;
	int wh,min;

	for(i=0;i<N;i++)sel[i] = ptexist[i] = -1;

	for(i=1;i<N;i++){
		for( j=0 ; j<e[i].size() ; j++ ){
			if(sel[i] == -1 || e[i][sel[i]].dist > e[i][j].dist){
				sel[i] = j;
			}
		}
	}

	for(i=1;i<N;i++)
		if(sel[i] == -1)
			return -1;

	for(i=1;i<N;i++)
		ret += e[i][sel[i]].dist;

	while( ( loop = checkloop() ) != NULL){
		i = contract(*loop);
		min=INF;
		for(j=0 ;j < e[i].size() ; j++){
			k=findpte(e[i][j].from);
			if(k == i)continue;
			if(min > e[i][j].dist){
				min = e[i][j].dist;
				wh = j;
			}
		}

		if(min == INF)
			return -1;

		sel[i] = wh;
		ret += e[i][wh].dist;
		delete loop;
	}
	return ret;

}

int main(){
	int T,t=1,m,u,v,w,i,j;

	cin >> T;

	while(T--){
		cin >> N >> m;
		for(i=0;i<N;i++)
			e[i].clear();
		for(i=0;i<m;i++){
			cin >> u >> v >> w;
			if(v==0)continue;
			if(u==v)continue;
			e[v].push_back(edge(u,w));
		}
		j=makemst();
		cout << "Case #" << (t++) << ": ";
		if(j==-1){
			cout << "Possums!" << endl;
		}else{
			cout << j << endl;
		}
	}
	return 0;
}
