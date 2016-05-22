#include<cmath>
#include<cstdio>
const int N = 1000;
bool notp[N];
main() {
	int i, j, n = 0, p[400];
	p[n++] = 2;
	for (i = 3; i < N; i += 2) {
		if (notp[i]) continue;
		for (j = i*i; j < N; j += i*2)
			notp[j] = 1;
		p[n++] = i;
	}
	puts("1");
	puts("0");
	puts("0");
	int m = 128;
	printf("%d\n", m);
	int k, l;
//	printf("%lf\n", m*(pow(2, 1.0/m)-1));
	while (scanf("%d", &l) == 1) {
		double r = 0;
		for (i = n - 1; i > n - m; --i) {
			if (i > l) k = 3;
			else k = 2;
			printf("%d %d\n", k, p[i]);
			r += k*1.0/p[i];
		}
		printf("%lf\n", r);
	}
}
