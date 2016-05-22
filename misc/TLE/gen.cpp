#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
	srand(time(NULL));
	puts("16");
	for(int i=0;i<16;i++)
		printf("%d\n",rand());
}
