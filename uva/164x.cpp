#include<stdio.h>
int lcs[20][20];
void trace(int i,int j){
	if(!i && !j)return;
	else if(i && j s[i]==s[j])
		trace(i-1,j-1);
	else if(i && lcs[i][j]==lcs[i-1][j])
		trace(i-1,j);
	else trace(i,j-1);
	???
}
main(){
int i,j;
while(scanf("%s",s1) && s1[0]!='#'){
	scanf("%s",s2);
	if(s1[0]==s2[0])lcs[0][0]=1;
	for(i=1;s1[i];i++)
		if(s2[0]==s1[i])
			lcs[i][0]=1;
		else if(lcs[i-1][0])
			lcs[i][0]=1;
	for(i=1;s2[i];i++)
		if(s1[0]==s2[i])
			lcs[0][i]=1;			
		else if(lcs[0][i-1])
			lcs[0][i]=1;
	for(i=1;s1[i];i++)
		for(j=1;s2[j];j++)
			if(s1[i]==s2[j])
				lcs[i][j]=lcs[i-1][j-1]+1;
			else if(lcs[i-1][j]>=lcs[i][j-1])
				lcs[i][j]=lcs[i-1][j];
			else
				lcs[i][j]=lcs[i][j-1];
	for(i=0;s1[i];i++);
	for(j=0;s2[j];j++);
	trace(i-1,j-1);
}
}