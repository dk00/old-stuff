inline int rank(unsigned x)
{
	int i,t=0;
	for(i=7311616;i>0;i/=52)
		t=t*13+(((x/i)%52)/4);
	return t;
}
struct hand
{
    unsigned h;
    hand(){}
    bool operator<(hand a)const{
        if(h/380204032!=a.h/380204032)
			return h/380204032<a.h/380204032;
        return rank(h%380204032)<rank(a.h%380204032);
    }
	bool operator==(hand a)const{
        if(h/380204032!=a.h/380204032)
			return 0;
        return rank(h%380204032)==rank(a.h%380204032);
	}
    hand(int a,int b){h=a+b*380204032ll;}
	void print()
	{
		unsigned i,j;
		for(i=0,j=h;i<5;i++,j/=52)
			printf("%c%c ",rk[j%52/4],su[j%52%4]);
		puts("");
	}
}s0[2598920],*s1=s0+1296420;
inline int test(int card[])
{
	char c[52],s[4],x[26];
	fill(s,s+4,0);
	fill(x,x+26,0);
	fill(c,c+52,0);
    int i,j,y,z;
	for(i=0;i<m;i++)
		s[card[i]%4]++,x[card[i]/4]++,c[card[i]]++;
	char k=0,f=0,S=0,t=0,tp=0,p=0;
    for(i=0;i<13;i++)
    {
        if(x[i]==4)k=1;
        if(x[i]==3)t=1;
        if(x[i]==2)
        {
            if(!p)p=1;
            else tp=1;
        }
        x[i+13]=x[i];
    }
	for(i=0;i<4;i++)
        if(s[i]>=5)f=1;
    for(i=0;i<9;i++)
        if(x[i] && x[i+1] && x[i+2] && x[i+3] && x[i+4])
            S=1;
	if(x[12] && x[0] && x[1] && x[2] && x[3])
		S=1;
    j=0;
    if(p)j=1;
    if(tp)j=2;
    if(t)j=3;
    if(S)j=4;
    if(f)j=5;
    if(t && p)j=6;
    if(k)j=7;
    if(f && S)
	{	
		for(i=z=0;z<5 && i<52;i++)
		{
			y=i/13+(i%13)*4;
			if(y/4==0)z=0;
			if(c[y])z++;
			else z=0;
			if(y/4==3 && c[y%4+48])z++;
		}
		if(z>=5)j=8,print(card);

	}
	printf("%d ",j);
	return j;
}

