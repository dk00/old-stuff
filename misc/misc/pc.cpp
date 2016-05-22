#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int p[40000][9];
char s[40000],c[9][9];
main(){
	int t,n,i,j,k,tmp;
	freopen("pc.in","r",stdin);
	for(scanf("%d%*c",&t);t>0;t--){
		gets(c[0]);
		gets(c[1]);
		gets(c[2]);
		gets(s);
		//scanf("%s%s%s%s",c[0],c[1],c[2],s);
		memset(p,-1,sizeof(p));
		n=strlen(s);
		for(i=0;c[0][i]!=0;i++)
			if(s[0]==c[0][i])
				p[0][i]=0;
			else p[0][i]=1;
		for(i=1;i<n;i++){
			for(j=0;c[i%3][j]!=0;j++){
				tmp=n;
				for(k=0;c[(i-1)%3][k]!=0;k++)
					if(c[i%3][j]!=c[(i-1)%3][k]){
						if(c[i%3][j]==s[i]){
							if(tmp>p[i-1][k])
								tmp=p[i-1][k];
						}
						else if(tmp>p[i-1][k]+1)
							tmp=p[i-1][k]+1;
					}
				p[i][j]=tmp;
			}
		}
		/*for(i=0;i<n;i++){
			for(j=0;c[i%3][j]!=0;j++)
				printf("%d ",p[i][j]);
			puts("");
		}*/
		j=n-1,k=n;
		for(i=0;c[2][i]!=0;i++)
			if(k>p[j][i])
				k=p[j][i];
		printf("%d\n",k);
	}
}

