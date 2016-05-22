#include<stdio.h>
#include<string.h>
char head[5000][55],name[5000][55];
int cost[5000],hl[5000];
int main(){
int i,n,time;
char num[100],*ptr;
for(n=0;scanf("%s",head[n]) && strcmp(head[n],"000000");n++){
	scanf("%s",name[n]);
	for(ptr=name[n];*ptr!='$';ptr++);
	*ptr=0;
	sscanf(ptr+1,"%d",&cost[n]);
	hl[n]=strlen(head[n]);
}
for(i='1';i<='9';i++){
	head[n][0]=i;
	head[n][1]=0;
	strcpy(name[n],"Local");
	cost[n]=0;
	hl[n++]=1;
}
strcpy(name[n],"Unknown");
while(scanf("%s",num) && strcmp(num,"#")){
	scanf("%d",&time);
	for(i=0;i<n;i++)
		if(!strncmp(head[i],num,hl[i]))break;
	hl[n]=strlen(num);
	printf("%-16s%-25s%10s%5d",num,name[i],num+(hl[i]==1?0:hl[i]),time);
	if(i<n)printf("%6.2lf %6.2lf\n",cost[i]/100.0,cost[i]*time/100.0);
	else printf("%6s %6.2lf\n","",-1.0);		
}
}