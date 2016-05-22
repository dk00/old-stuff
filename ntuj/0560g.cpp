#include<ctime>
#include<cstdio>
#include<cstdlib>
main()
{
    srand(time(NULL));
    int i,j,k,n=25,m=2,c=2,t=1;
    while(t--){
	printf("           %d %d\n",n,m);
	for(i=0;i<m;i++){
	    j=10;
	    while(j--)putchar(rand()%c+'a');
	    puts("");
	}
    }
    puts("0 0");
}
