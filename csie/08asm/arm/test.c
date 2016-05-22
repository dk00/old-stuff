typedef unsigned short u16;
typedef unsigned u32;
inline u32 f(u32 t){return (t&0x1F)|((t&0x3E0)<<4)|((t&0x7C00)<<8);}
inline u32 g(u32 t,u32 c)
{return ((t&0x1FF)/c)|((((t>>18)&0x1FF)/c)<<10)|((((t>>9)&0x1FF)/c)<<5);}
u32 tmp[3][250];
void myfilter(u16 *ret,const u16* ori) {
	u32 i,j,c0,c1;
	u32 *t0=tmp[0]+5,*t1=tmp[1]+5,*t2=tmp[2]+5,*t3;
	for(j=0;j<240;j++)
		t0[j]=t1[j]=t2[j]=0;
	for(i=0;i<160;i++)
	{
		for(j=0;j<240;j++)
		{
			register u32 t=ori[i*240+j];
			t=f(t);
			t1[j-1]+=t;
			t1[j-1]+=t;
			t2[j-1]+=t;
			t0[j]+=t;
			t1[j]+=t;
			t2[j]+=t;
			t0[j+1]+=t;
			t1[j+1]+=t;
			t2[j+1]+=t;
		}
		if(i)
		{
			c0=6,c1=9;
			if(i==1)c0=4,c1=6;
			ret[i*240-240]=g(t0[0],c0);
			for(j=1;j<239;j++)
				ret[i*240+j-240]=g(t0[j],c1);
			ret[i*240-1]=g(t0[239],c0);
		}
		for(j=0;j<240;j++)t0[j]=0;
		t3=t0,t0=t1,t1=t2,t2=t3;
	}
	ret[i*240-240]=g(t0[0],4);
	for(j=1;j<239;j++)
		ret[i*240+j-240]=g(t0[j],6);
	ret[i*240-1]=g(t0[239],6);
}
void boxfilter(u16 *ret,const u16* ori) {
	u32 r,g,b;
	u32 cc;
	int x,y,dx,dy;

	for(y=0;y<160;y++) {
	    for(x=0;x<240;x++) {
	        cc = r = g = b = 0;
            for(dy = -1;dy<=1;dy++) {
	            for(dx=-1;dx<=1;dx++) {
	                int nx = x+dx;
	                int ny = y+dy;
                    u16 ncolor;
                    if(nx < 0 || ny < 0 || nx >=240 || ny >= 160) continue;
                    ncolor = ori[ny*240+nx];
                    cc++;
                    r+= (ncolor&0x001f);
                    g+= ((ncolor&0x03e0)>>5);
                    b+= ((ncolor&0x7c00)>>10);
                }
            }
            r = r/cc;
            g = g/cc;
            b = b/cc;
            ret[y*240+x] = (b<<10)+ (g<<5) + r;
        }
    }
}
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
u16 s0[38400],s1[38400],t0[38400],t1[38400];
main()
{
	int i,N=38400;
	srand(time(NULL));
	for(i=0;i<N;i++)
		s0[i]=s1[i]=rand()%32768;
	boxfilter(t0,s0);
	myfilter(t1,s1);
	printf("%d %d\n",t0[0],s0[0]);
	for(i=0;i<N;i++)
		if(t0[i]!=t1[i])
		{
			puts("!");
			break;
		}
}
