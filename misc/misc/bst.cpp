template<typename o> struct node{
	int t[2];
	o d[2];
	node *l[2],*r[2];
	node(){t0=t1=0;l0=r0=l1=r1=NULL;}
	node *insert(o x,int nt)
	{
		if(!t[0])
		{
			t[0]=nt;
			d[0]=x;
		}
		node **to;
		if(o<d[p])to=&l[p];
		else to=&r[p];
		if(*to && *to->t[1])
		{
		
		}

	}
};
