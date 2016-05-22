#include<algorithm>
int n,m,i,j,k,t,tr[1001],num[1001],nu,back_odd[1001],back_even[1001],an,
	map[1001][1001],level[1001];
void dfs(int x,int le,int anc){ //點的編號 及 第幾層 及 父親
	int ii;
	num[x]=nu++;   //第幾個搜尋到的點
	back_odd[x]=back_even[x]=n;  //可回溯到的 奇圈點 及 偶圈點
	tr[x]=t;  //此點已測試過
	level[x]=le;    //此點為第幾層
	//開始測試所有可連接的邊
	for(ii=1;ii<map[x][0];ii++)
		if(tr[map[x][ii]]!=t){    //如果ii不是x的祖先
			dfs(map[x][ii],le+1,x);
			back_even[x]<?=back_even[map[x][ii]];
			back_odd[x]<?=back_odd[map[x][ii]];
			//子孫可回溯的地方,自己也必然可回溯
		}
		else if(map[x][ii]!=anc){            //如果ii是x的祖先但不是父親
			if((level[x]-level[map[x][ii]])%2==0)    //此回溯為奇圈
				back_odd[x]<?=num[map[x][ii]];
			else                             //此回溯為偶圈
				back_even[x]<?=num[map[x][ii]];
		}
	if(back_odd[x]<num[x])back_odd[x]<?=back_even[x];
}
main(){
	while(scanf("%d %d",&n,&m)&&n+m){
		t++;
		nu=0;
		an=0;
		//設定初始值
		for(i=1;i<=n;i++)map[i][i]=t;
		//此為簡單圖,自動去掉連到自己的邊
		for(i=0;i<m;i++){
			scanf("%d %d",&j,&k);
			map[j][k]=map[k][j]=t;
		}
		//讀入沒連結的邊
		for(i=1;i<=n;i++)
			for(j=1,map[i][0]=1;j<=n;j++)
				if(map[i][j]!=t)map[i][map[i][0]++]=j;
					for(i=1;i<=n;i++){
						nu=0;
						t++;
						dfs(i,0,-1);
						if(back_odd[i]>num[i])an++;
					}
		//對於每個獨立的聯通圖各別做測試
		printf("%d\n",an);
	}
}
