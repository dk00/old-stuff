#include <stdio.h>
#include <stdlib.h>
char a[500005];
int main(void)
{
	int T, i;
	gets(a);
	T = atoi(a);
	while(T--){
		gets(a);
		int s = -1, mx = 0, len = 0, c = 0;
		for(i=0;a[i];i++);
		a[i] = ' ';
		a[i+1]='\0';
		for(i=0;a[i];i++){
			if(a[i] != ' ')
				++len;
			else if(len != 0 && s != len) {
				s = len;
				len = 0;
				c = 1;
				if(mx < 1) mx = 1;
			} else if(len != 0 && s == len) {
				if(mx < ++c) mx = c;
				len = 0;
			}
		}
		printf("%d\n", mx);
	}
	return 0;
}
