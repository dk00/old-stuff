#include<ctime>
#include<cstdio>
main(int m,char **arg)
{
	if(m<2)return 0;
	FILE *fp=fopen(arg[1],"rb");
	if(!fp)return 0;
	const unsigned N=0x3B10;
	unsigned buf=0,read,sum;
//	for(unsigned j=2;j<257;j++)
	{
		fseek(fp,0,SEEK_SET);
		for(unsigned i=0;i<3;i++)
		{
			read=48;
			fseek(fp,48,SEEK_CUR);
			unsigned c[4]={0};
			for(sum=0;read<N;read+=fread(&buf,1,4,fp))
			{
				sum+=buf;
				c[0]+=buf&255;
				c[1]+=(buf>>8)&255;
				c[2]+=(buf>>16)&255;
				c[3]+=(buf>>24)&255;
			}
			printf("%X %X %X %X\n",c[0],c[1],c[2],c[3],c[4]);
			printf("%X\n",sum);
		}
	}
	fclose(fp);
	printf("%X\n",time(NULL));
}
