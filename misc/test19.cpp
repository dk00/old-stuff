#include<stdio.h>
const int M=500003,D=11;
int tt,tr[M],hash[M][24],back[M],a[24],exam[M],bfs[M],tim[M];
int ini[24]={0,3,4,3,0,5,6,5,0,1,2,1,0,7,8,7,0,9,10,9,0,1,2,1};
bool same(int x,int b[]){
	int i;
	for(i=0;i<24;i++)
		if(b[i]!=hash[x][i])break;
	if(i==24)return 1;
	return 0;
}
void print1(int x){
	if(x==-1)return;
	if(exam[x]==1)putchar('3');
	if(exam[x]==2)putchar('4');
	if(exam[x]==3)putchar('1');
	if(exam[x]==4)putchar('2');
	print1(back[x]);
}
void print2(int x){
	if(back[x]==-1)return;
	print2(back[x]);
	printf("%d",exam[x]);
}
int step(int &i,int &j,int &l,int x,int y,int z,bool ret)
{
	int k,tg=ret?tt:-1;
	for(k=0;k<12;k++)
		a[k+z]=hash[bfs[i]][(k+x)%12+z];
	for(k=12-z;k<21-z;k++)a[k]=hash[bfs[i]][k];
	for(k=0;k<3;k++)a[21-z+k]=a[9+z+k];
	for(k=l=0;k<24;k++){
		l*=D;
		l+=a[k];
		l%=M;
	}
	while(tr[l]==-1 || (ret && tr[l]==tt)){
		if(same(l,a)==1)break;
		l++;
		if(l==M)l=0;
	}
	if(ret && tr[l]==-1)
		return y;
	if(tr[l]!=tg){
		tr[l]=tg;
		for(k=0;k<24;k++)hash[l][k]=a[k];
		exam[l]=y;
		tim[l]=tim[bfs[i]]+1;
		back[l]=bfs[i];
		bfs[j++]=l;
	}
	return 0;
}
main(){
	int i,j,k,l,t,r,rr;
	for(i=k=0;i<24;i++){
		k*=D;
		k+=ini[i];
		k%=M;
	}
	for(i=0;i<24;i++)hash[k][i]=ini[i];
	tr[k]=-1;
	back[k]=-1;
	bfs[0]=k;
	tim[k]=0;
	for(i=0,j=1;tim[bfs[i]]<8;i++){
		if(exam[bfs[i]]!=3)
			step(i,j,l,10,1,0,0);
		if(exam[bfs[i]]!=4)
			step(i,j,l,2,2,12,0);
		if(exam[bfs[i]]!=1)
			step(i,j,l,2,3,0,0);
		if(exam[bfs[i]]!=2)
			step(i,j,l,10,4,12,0);
	}
	scanf("%d",&t);
	while(t--){
		for(i=k=0;i<24;i++){
			scanf("%d",&a[i]);
			k*=D;
			k+=a[i];
			k%=M;
		}
		while(tr[k]==-1){
			if(same(k,a)==1)break;
			k++;
			if(k==M)k=0;
		}
		if(tr[k]==-1){
			if(tim[k]==0)puts("PUZZLE ALREADY SOLVED");
			else{
				print1(k);
				puts("");
			}
		}
		else{
			tt++;
			for(i=0;i<24;i++)hash[k][i]=a[i];
			bfs[0]=k;
			exam[k]=0;
			tim[k]=0;
			back[k]=-1;
			tr[k]=tt;
			for(i=0,j=1;tim[bfs[i]]<8;i++){
				if(exam[bfs[i]]!=3 && (r=step(i,j,l,10,1,0,1))>0)
					break;
				if(exam[bfs[i]]!=4 && (r=step(i,j,l,2,2,12,1))>0)
					break;
				if(exam[bfs[i]]!=1 && (r=step(i,j,l,2,3,0,1))>0)
					break;
				if(exam[bfs[i]]!=2 && (r=step(i,j,l,10,4,12,1))>0)
					break;
			}
			if(tim[bfs[i]]>=8)puts("NO SOLUTION WAS FOUND IN 16 STEPS");
			else{
				print2(bfs[i]);
				printf("%d",r);
				print1(l);
				puts("");
			}
		}
	}
}
