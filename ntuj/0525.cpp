#include<cstdio>
main()
{
	char s[99];
	int i,j;
	while(gets(s)!=NULL){
		for(i=j=0;s[i];i++)
				if(s[i]>='0'&&s[i]<='9')printf("9"),j++;
		if(!j)printf("0");
		puts("");
	}
}
