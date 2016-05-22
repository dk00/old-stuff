typedef unsigned u32;
main()
{
	u32 tmp[3][242];
	u32 *t0=&tmp[0][1],*t1=&tmp[1][1],*t2=&tmp[2][1],*t3;
	t0[-1]=1;
	printf("%08x %08x\n",t0,tmp[0]);
}
