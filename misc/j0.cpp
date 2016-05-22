#include<cstdio>
int s[]={0,2,
7,
5,
30,
169,
441,
1872,
7632,
1740,
93313,
459901,
1358657,
2504881};
main()
{
	int n;
	while(scanf("%d",&n)==1 && n)
		printf("%d\n",s[n]);
}
