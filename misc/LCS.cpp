#include<stdio.h>
main()
{
	int i,j,k,l1,l2,length[100][100];
	char a[100],b[100],lcs[100][100][100];
	for(i=1;i==i;i++)
	{
		scanf("%c",&a[i]);
		if(a[i]=='\n')
			break;
	}
	l1=i-1;
	for(i=1;i==i;i++)
	{
		scanf("%c",&b[i]);
		if(b[i]=='\n')
			break;
	}
	l2=i-1;
/*
l1,l2分別為序列a,b的長度
若用length[j][i]表示a序列的前j項, b序列的前i項的最長共同子序列之長度
(例如在abcd, bdac的例子中,
length[3][3]表示abc和bda的最長共同子序列之長度)
則有遞迴式:
if(a[j]==b[i])
	length[j][i]=length[j-1][i-1];
else
	length[j][i]=max(length[j-1][i], length[j][i-1]);
若不只要紀錄長度, 而要同時紀錄該序列的話
用lcs[j][i][]表示長度為length[j][i]的子序列
則有(當然實際上的code不是那樣寫的):
if(a[j]==b[i])
	lcs[j][i][]=lcs[j-1][i-1][];
else
	lcs[j][i][]=max(lcs[j-1][i][], lcs[j][i-1][]);
*/
	for(i=0;i<=l1;i++)
		length[i][0]=0;
	for(i=1;i<=l2;i++)
		length[0][i]=0;
	for(i=1;i<=l1;i++)
	{
		for(j=1;j<=l2;j++)
		{
			if(a[i]==b[j])
			{
				length[i][j]=length[i-1][j-1]+1;
				for(k=0;k<length[i-1][j-1];k++)
					lcs[i][j][k]=lcs[i-1][j-1][k];
				lcs[i][j][length[i-1][j-1]]=a[i];
			}
			else
			{
				if(length[i][j-1]>length[i-1][j])
				{
					length[i][j]=length[i][j-1];
					for(k=0;k<length[i][j];k++)
						lcs[i][j][k]=lcs[i][j-1][k];
				}
				else
				{
					length[i][j]=length[i-1][j];
					for(k=0;k<length[i][j];k++)
						lcs[i][j][k]=lcs[i-1][j][k];
				}
			}
		}
	}
	printf("%d\n",length[l1][l2]);
	for(k=0;k<length[l1][l2];k++)
		printf("%c",lcs[l1][l2][k]);
	printf("\n");
	scanf("%d",&i);
}
