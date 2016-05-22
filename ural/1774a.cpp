#include <stdio.h>
#include <queue>

int a[105], b[105];
int c[105][2], nc[105];


int n;

int getone(int t)
{
	int mi=-1, i;
	for(i=0;i<n;i++){
		if(nc[i]<2 && a[i]<=t 
        && (nc[i]==0 || nc[i]>0 && c[i][nc[i]-1] != t)
				&& (mi==-1 || a[i]+b[i]+nc[i] < a[mi]+b[mi]+nc[mi]))
			mi = i;
	}
  if(mi!=-1){
  	c[mi][nc[mi]++] = t;
  	if (t >= a[mi] + b[mi])
  		return -1;
  }else if(mi==-1){
    mi = -3;
  }
	return mi;
}

int main(void)
{
	int k, i;
	scanf("%d%d", &n, &k);
	for(i=0;i<n;i++){
		scanf("%d%d", &a[i], &b[i]);
	}
	int ti=0;
	int f = 0, sv=0;
	while(sv < n*2) {
		for(i=0;i<k;i++){
			f = getone(ti);
			if(f<0) break;
			++sv;
		}
		++ti;
    if(f==-3) continue;
		if(f<0) break;
	}
	if(sv == n * 2){
		printf("Yes\n");
		for(i=0;i<n;i++)
			printf("%d %d\n", c[i][0], c[i][1]);
	}else
		printf("No\n");
	return 0;
}

