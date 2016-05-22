#define defaultn 50
#define defaultm 50
class matrix{
public:
	int n,m,s[defaultn][defaultm];
	matrix& operator*=(const matrix& b){
		int i,j,k;
		matrix a=*this;
		for(i=0;i<a.n;i++)
			for(j=0;j<b.m;j++)
				for(k=s[i][j]=0;k<n;k++)
					s[i][j]+=a.s[i][k]*b.s[k][j];
		return *this;
	}
	void get(int pn,int pm){
		n=pn,m=pm;
		int i,j;
		for(i=0;i<n;i++)
			for(j=0;j<m;j++)
				scanf("%d",&s[i][j]);
	}
	void print(){
		int i,j;
		for(i=0;i<n;i++){
			printf("%d",s[i][0]);
			for(j=1;j<m;j++)
				printf(" %d",s[i][j]);
			puts("");
		}
	}
};