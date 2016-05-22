#include<cstdio>
char t0[9999],t1[9999];
int fgetline(char buf[],FILE *fp)
{
	int n,c;
	c=fgetc(fp);
	if(c==EOF)return -1;
	buf[0]=c;
	for(n=1;(c=fgetc(fp))!='\n' && c!=EOF;n++)
		buf[n]=c;
	buf[n++]='\n';
	buf[n]=0;
	return n;
}
main()
{
	int x;
	while(scanf("%d",&x)==1)
	{
		FILE *f0,*f1,*f2;
		sprintf(t0,"%02d.ass",x);
		f0=fopen(t0,"rb");
		if(!f0)continue;
		puts("0");
		sprintf(t0,"%02da.ass",x);
		f1=fopen(t0,"rb");
		if(!f1)continue;
		puts("1");
		f2=fopen("res","wb");
		while(fgetline(t0,f0)>0 && fgetline(t1,f1)>0)
		{
			if(t0[0]=='D' && t1[0]=='D')
				for(int i=0;i<40;i++)
					t1[i]=t0[i];
			puts(t0);
			puts(t1);
			fputs(t1,f2);
		}
		fclose(f0);
		fclose(f1);
		fclose(f2);
	}
}
