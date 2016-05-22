#include <stdio.h>

int main(void)
{
	int cs = 0, n, i;
	while(scanf("%d", &n)!=EOF){
		if(n==0) break;
		int ans=0, x;
		for(i=0;i<n;i++) {
			scanf("%d", &x);
			if(x>0) ++ans;
			else if(x==0) --ans;
		}
		printf("Case %d: %d\n", ++cs, ans);
	}
	return 0;
}
