/*
ID: s0000151
PROG: latin
LANG: C++
*/
#include<stdio.h>
int n,fact[7],sq[7][7],row[7][7],col[7][7];
long long soln;
void dfs0(int c,int r);
void dfs1(int r,int c);
void dfs2(int c,int r);
main(){
freopen("latin.in","r",stdin);
freopen("latin.out","w",stdout);
int i;
for(fact[0]=n=1;n<7;n++)fact[n]=fact[n-1]*n;
scanf("%d",&n);
for(i=0;i<n;i++){
    row[0][i]=col[i][i]=1;
    row[i][i]=col[0][i]=1;
    sq[0][i]=i+1;
    sq[i][0]=i+1;
}
/*if(n==7){
	soln=16942080;
	printf("%lld\n",soln*fact[n-1]);
	return 0;
}*/
dfs1(1,1);
printf("%d\n",soln*fact[n-1]);
}
void dfs2(int c,int r){
    if(r>=n){
		dfs1(c+1,c+1);
		return;
	}
	if(c==r){
		dfs2(c,r+1);
		return;
	}
	for(int i=0;i<n;i++)
	    if(!row[r][i] && !col[c][i]){
			row[r][i]=col[c][i]=1;
			sq[r][c]=i+1;
			dfs2(c,r+1);
			row[r][i]=col[c][i]=0;
		}
}
void dfs1(int r,int c){
    if(r>=n-1){
        soln++;
        return;
    }
    if(c>=n){
        dfs2(r,r);
        return;
    }
    for(int i=0;i<n;i++)
		if(!row[r][i] && !col[c][i]){
            row[r][i]=col[c][i]=1;
            sq[r][c]=i+1;
            dfs1(r,c+1);
            row[r][i]=col[c][i]=0;
		}
}
void dfs0(int c,int r){
    if(r>=n){
		dfs1(1,1);
		return;
	}
	for(int i=0;i<n;i++)
	    if(!row[r][i] && !col[c][i]){
			row[r][i]=col[c][i]=1;
			sq[r][c]=i+1;
			dfs0(c,r+1);
			row[r][i]=col[c][i]=0;
		}
}
