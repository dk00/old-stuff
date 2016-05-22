#include<map>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
map<string,int> num;
string roman[10001],err="Err[o]r";
const char *getroman(int x)
{
	if(x<0 || x>10000)return err.c_str();
	return roman[x].c_str();
}
string sub[]={"M","CM","DCCC","DCC","DC","D","CD","CCC","CC","C","XC",
	"LXXX","LXX","LX","L","XL","XXX","XX","X","IX","VIII","VII","VI","V",
	"IV","III","II","I",""};
int val[]={1000,900,800,700,600,500,400,300,200,100,90,80,70,60,50,40,30,
	20,10,9,8,7,6,5,4,3,2,1,0};
void init()
{
	int i,j,k;
	roman[0]="O";
	for(i=1;i<=10000;i++)
	{
//		printf("%d\n",i);
		for(k=i,j=0,roman[i]="";k>0;)
		{
			while(val[j]>0 && val[j]>k)j++;
			while(val[j]<=k)
			{
				k-=val[j];
				roman[i]+=sub[j];
			}
		}
//		puts(roman[i].c_str());
		num[roman[i]]=i;
	}
}
int error,reg[10],u[10];
int parseval(char tmp[])
{
	if('0'<=tmp[0] && tmp[0]<='9')
	{
		if(!u[tmp[0]-'0'])error=1;
		return reg[tmp[0]-'0'];
	}
	return num[tmp];
}
main()
{
	int i,j,k;
	char tmp[99];
	init();
	while(scanf("%[^=\n]",tmp)>0 && strcmp(tmp,"QUIT"))
	{
		if(!strcmp(tmp,"RESET"))
		{
			scanf("%*[\n]");
			memset(u,0,sizeof(u));
			memset(reg,-1,sizeof(reg));
			puts("Rea[d]y");
			continue;
		}

//		printf("%s",tmp);
		i=parseval(tmp);
//		printf("(%d)\n",i);
		int r=reg[k=tmp[0]-'0'];

		scanf("%[=\n]",tmp);
//		printf("%s",tmp);
//		printf("(%d)\n",parseval(tmp));
		error=0;
		scanf("%[^+-\n]",tmp);
		j=parseval(tmp);
		r=j;

		while(scanf("%[+-\n]",tmp) && tmp[0]!='\n')
		{
			if(tmp[0]=='+')j=1;
			else j=-1;
			scanf("%[^+-\n]",tmp);
//			printf("%s",tmp);
//			printf("(%d)\n",parseval(tmp));
			j*=parseval(tmp);
			r+=j;
		}
		if(r<0 || r>10000)error=1;
		if(error)puts(getroman(-1));
		else u[k]=1,printf("%d=[%s]\n",k,getroman(reg[k]=r));
	}
	puts("Bye");
	return 0;
}
