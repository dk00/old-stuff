a()
{
	unsigned i,j,x;
	scanf("%u",&x);
	for(i=1u<<31;i&&(i&~x);i/=2);
	for(j=1;(x&i?x&j:(j&~x))&&i>j;i/=2,j*=2);
	return i>j;
}
main(T,x)
{
	for(scanf("%d",&T);T--;puts(a()?"NO":"YES"))
	{}
}
