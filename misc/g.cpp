#include<stdio.h>
const int N=99;
int g,n,d,s,line[N][N],i,j,k,l,st[N],a,b,bus[N][N],di[N];
char c;
int gcd(int x,int y){
	while((x%=y)&&(y%=x));
	return x+y;
}
void disjoint(int x,int y){
	int ii,jj;
	for(ii=x;ii!=di[ii];ii=di[ii]);
	for(jj=y;jj!=di[jj];jj=di[jj]);
	di[ii]=jj;
}
int ab(int x,int y){return x<y?y-x:x-y;}
main(){
	while(scanf("%d %d %d",&n,&d,&s)&&n){
		for(i=1;i<=d;i++)di[i]=i;
		for(i=0;i<n;i++){
			for(j=0;scanf("%d%c",&line[i][j++],&c)&&c!='\n';);
			st[i]=j;
			while(scanf("%d %d%c",&a,&b,&c)){
				for(j=0;j<st[i];j++)
					if(line[i][j]==a)break;
				bus[b][0]=i;
				bus[b][1]=j;
				if(c=='\n')break;
			}
		}
		for(i=1;i<=d;i++)
			for(j=i+1;j<=d;j++){
				g=gcd(st[bus[i][0]],st[bus[j][0]]);
				for(k=0;k<st[bus[i][0]];k++){
					for(l=0;l<st[bus[j][0]];l++)
						if(line[bus[i][0]][k]==line[bus[j][0]][l])break;
					if(l<st[bus[j][0]]){
						if(ab((k-bus[i][1]+st[bus[i][0]])%st[bus[i][0]]
							,(l-bus[j][1]+st[bus[j][0]])%st[bus[j][0]])%g==0){
							disjoint(i,j);
							break;
						}
					}
				}
			}
		for(i=2;i<=d;i++){
			for(j=i;j!=di[j];j=di[j]);
			for(k=i-1;k!=di[k];k=di[k]);
			if(j!=k)break;
		}
		if(i>d)puts("Yes");
		else puts("No");
	}
}
/*
0 1 0 0
0 1 1 1
0 1 2 2
0 2 0 0
0 2 1 1
0 2 2 2
1 2 0 0
1 2 1 1
1 2 2 2

 */
