#include<cstdio>
char a[100088],b[100089];
int s1[100088];
main()
{
	int i,j,k;
	while(gets(a+2) && gets(b))
	{
		a[0]='2';
		a[1]='0';
		for(i=0;a[i];i++,i++)
		{
			k=a[i+2],a[i+2]=0;
			sscanf(a+i,"%02X",s1+i/2);
			a[i+2]=k;
		}
		for(i=0;b[i];i++,i++)
		{
			k=b[i+2],b[i+2]=0;
			sscanf(b+i,"%02X",&j);
			b[i+2]=k;
			s1[i/2]^=j^(i?s1[i/2-1]:0);
		}
		for(j=0;j<i/2;j++)
			printf("%02X",s1[j]);
		puts("");
	}
}
//   05 26 2C 52 69143F314C2A69651A264B
//61 07 28 41 3B 63072C52222169720B425E
//
//
