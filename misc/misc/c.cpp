// c

#include <stdio.h>
#define MAXNUM 2000050
#define MOD 1000003

int n;
int C[MAXNUM],S[MAXNUM];

int main(void)
{
	int i;
	for(i=0,C[0]=1;i<MAXNUM-1;i++)
		C[i+1]=(int)(((long long)C[i]*(4*i+2)/(i+2))%MOD);
	for(i=2,S[0]=C[0],S[1]=C[1];i<MAXNUM;i++)
		S[i]=(S[i-2]+C[i])%MOD;
	while(scanf("%d",&n)==1) {
		if((n&1)||n<4) printf("0\n");
		else printf("%d\n",S[n/2-2]);
	}
	return 0;
}
