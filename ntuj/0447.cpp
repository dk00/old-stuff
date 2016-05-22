#include<cstdio>
struct pt{
	int x,y;
	pt operator-(pt a)const{
		return (pt){x-a.x,y-a.y};
	}
	pt operator*(pt a)const{
		return x*a.y-y*a.x;
	}
}s[999];
char in(pt s,pt t,pt o)
{
	return ((s.x==o.x || t.x==o.x)&&(s.y==o.y || t.y==o.y))||
	(((s.x<o.x)^(t.x<o.x)) && ((s.y<o.y)^(t.y<o.y)));
}
char ins(pt a0,pt a1,pt b0,pt b1)
{
	int d[]={(a1-a0)*(b0-a0),(a1-a0)*(b1-a0),
		(b1-b0)*(a0-b0),(b1-b0)*(a1-b0)};
	if(!d[0] && in(a0,a1,b0))return 1;
	if(!d[1] && in(a0,a1,b1))return 1;
	if(!d[2] && in(b0,b1,a0))return 1;
	if(!d[3] && in(b0,b1,a1))return 1;
	return ((d[0]<0)^(d[1]<0))&&((d[2]<0)^(d[3]<0));
}
inline int one(int x){return x<0?-1:x>0?1:0;}
bool intersect(int e,int f,int g,int h,int o,int p,int q,int r){
    if((e>?g)<(o<?q))return 0;
    if((e<?g)>(o>?q))return 0;
    if((f>?h)<(p<?r))return 0;
    if((f<?h)>(p>?r))return 0;
    int s=one((e-o)*(h-p)-(g-o)*(f-p)),
    t=one((e-q)*(h-r)-(g-q)*(f-r)),
    u=one((o-e)*(r-f)-(q-e)*(p-f)),
    v=one((o-g)*(r-h)-(q-g)*(p-h));
    if(s*t<=0&&v*u<=0)return 1;
    return 0;
}
main()
{
	while(1)
	{
		while(scanf(" %c ",&x) && (x!='-' || x!='.'))
		{
			scanf("%s",tmp);
			if(tmp==string("square"))
			{
			}
			if(tmp==string("line"))
			{
			}
			if(tmp==string("triangle"))
			{
			}
			if(tmp==string("polygon"))
			{
			}
			if(tmp==string("rectangle"))
			{
			}
		}
	}
}
