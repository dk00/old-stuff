#include<algorithm>
int n,m,i,j,k,t,tr[1001],num[1001],nu,back_odd[1001],back_even[1001],an,
	map[1001][1001],level[1001];
void dfs(int x,int le,int anc){ //�I���s�� �� �ĴX�h �� ����
	int ii;
	num[x]=nu++;   //�ĴX�ӷj�M�쪺�I
	back_odd[x]=back_even[x]=n;  //�i�^���쪺 �_���I �� �����I
	tr[x]=t;  //���I�w���չL
	level[x]=le;    //���I���ĴX�h
	//�}�l���թҦ��i�s������
	for(ii=1;ii<map[x][0];ii++)
		if(tr[map[x][ii]]!=t){    //�p�Gii���Ox������
			dfs(map[x][ii],le+1,x);
			back_even[x]<?=back_even[map[x][ii]];
			back_odd[x]<?=back_odd[map[x][ii]];
			//�l�]�i�^�����a��,�ۤv�]���M�i�^��
		}
		else if(map[x][ii]!=anc){            //�p�Gii�Ox�����������O����
			if((level[x]-level[map[x][ii]])%2==0)    //���^�����_��
				back_odd[x]<?=num[map[x][ii]];
			else                             //���^��������
				back_even[x]<?=num[map[x][ii]];
		}
	if(back_odd[x]<num[x])back_odd[x]<?=back_even[x];
}
main(){
	while(scanf("%d %d",&n,&m)&&n+m){
		t++;
		nu=0;
		an=0;
		//�]�w��l��
		for(i=1;i<=n;i++)map[i][i]=t;
		//����²���,�۰ʥh���s��ۤv����
		for(i=0;i<m;i++){
			scanf("%d %d",&j,&k);
			map[j][k]=map[k][j]=t;
		}
		//Ū�J�S�s������
		for(i=1;i<=n;i++)
			for(j=1,map[i][0]=1;j<=n;j++)
				if(map[i][j]!=t)map[i][map[i][0]++]=j;
					for(i=1;i<=n;i++){
						nu=0;
						t++;
						dfs(i,0,-1);
						if(back_odd[i]>num[i])an++;
					}
		//���C�ӿW�ߪ��p�q�ϦU�O������
		printf("%d\n",an);
	}
}
