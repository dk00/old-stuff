#include <stdio.h>

int go(int len, int x)
{
	int i, j;
	for(i=0;i<=len;i++){
		int r = 0;
		for(j=0;j<i;j++)
			r = (r * 10 + 8) % x;
		for(;j<len;j++)
			r = (r * 10 + 6) % x;
		if(r == 0) {
			for(j=0;j<i;j++)
				printf("8");
			for(;j<len;j++)
				printf("6");
			printf("\n");
			return 1;
		}
	}
	return 0;
}

int main(void)
{
	int T, i;
	scanf("%d", &T);
	while(T--){
		int x;
		scanf("%d", &x);
		if(x%5==0) { printf("-1\n"); continue; }
		for(i=1;i<=200;i++) {
			if(go(i, x)) break;
		}
		if(i > 200) printf("-1\n");
	}
	return 0;
}
