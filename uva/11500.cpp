/* p=at/6, q=1-p
 * n=v1/d+v2/d
 * [ 0 0 1 0 0 0]
 *   v1/d  v2/d
 *  
 *   1 q 0 0 0 0
 *   0 0 q 0 0 0
 *   0 p 0 q 0 0
 *   0 0 p 0 q 0
 *   0 0 0 p 0 0
 *   0 0 0 0 p 1
 *
 * */
#include<cstdio>
const int N=99;
void go(int n,int m,double c[N][N])
{
	int i,j,k;
	double t[N][N];
	while(m--)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				t[i][j]=c[i][j],c[i][j]=0;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				for(k=0;k<n;k++)
					c[i][k]+=t[j][k]*t[i][j];
	}
}
void print(int n,double c[N][N])
{
	int i,j;
	for(i=0;i<n;i++,puts(""))
		for(j=0;j<n;j++)
			printf("%.2lf ",c[i][j]);
}
main()
{
	int i,j,k,n,a;
	double p,c[N][N];
	while(scanf("%d %d %d %d",&i,&j,&n,&k)==4 && i+j+n+k)
	{
		p=n/6.0;
		n=(i-1)/k+(j-1)/k+3;
		a=(i-1)/k+1;
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				c[i][j]=0;
		for(i=1;i<n-1;i++)
			c[i-1][i]=1-p,c[i+1][i]=p;
		c[0][0]=1,c[n-1][n-1]=1;
		go(n,100,c);
		printf("%.1lf\n",100*c[n-1][a]+1e-7);
	}
}
