/*
ID: s0000151
PROG: window
LANG: C++
*/
#include<stdio.h>
#include<stdlib.h>
struct llt{
	char c;
	int sx,sy,ex,ey;
	llt *next;
}*last,*ptr,*top=NULL,*bottom=NULL;
struct _rect{
	char c;
	int sx,sy,ex,ey;
}rect[10000],a,b,c,d;
int exist[256];
_rect __rect(int c,int sx,int sy,int ex,int ey){
	_rect tmp;
	tmp.c=c,tmp.sx=sx,tmp.sy=sy,tmp.ex=ex,tmp.ey=ey;
	return tmp;
}
void create(char w,int sx,int sy,int ex,int ey);
void del(char w);
void move_to_top(char w);
void move_to_bottom(char w);
void show(char w);
main(){
freopen("window.in","r",stdin);
freopen("window.out","w",stdout);
char cmd,w,br;
int cx1,cy1,cx2,cy2;
create('=',1,1,1,1);
while(scanf("%c",&cmd)!=EOF){
	if(cmd=='w')scanf("(%c,%d,%d,%d,%d)%c",&w,&cx1,&cy1,&cx2,&cy2,&br);
	else scanf("(%c)%c",&w,&br);
	switch(cmd){
	case 'w':
		if(!exist[w])
		    create(w,cx1,cy1,cx2,cy2);
		break;
	case 't':
		if(exist[w])
		    move_to_top(w);
		break;
	case 'b':
		if(exist[w])
		    move_to_bottom(w);
		break;
	case 'd':
		if(exist[w])
		    del(w);
		break;
	case 's':
		if(exist[w])
		    show(w);
		break;
	}
}
}
void create(char w,int sx,int sy,int ex,int ey){
	if(sx>ex){
		sx+=ex;
		ex=sx-ex;
		sx-=ex;
	}
	if(sy>ey){
		sy+=ey;
		ey=sy-ey;
		sy-=ey;
	}
    ptr=(llt *)malloc(sizeof(llt));
    if(bottom==NULL)top=bottom=ptr;
	ptr->c=w;
	ptr->sx=sx;
	ptr->sy=sy;
	ptr->ex=ex-1;
	ptr->ey=ey-1;
	ptr->next=NULL;
	top=top->next=ptr;
	exist[w]=1;
}
void del(char w){
	if(bottom->c==w){
		ptr=bottom;
		bottom=bottom->next;
	}
	else{
		for(ptr=bottom;ptr!=NULL && ptr->c!=w;last=ptr,ptr=ptr->next);
		last->next=ptr->next;
	}
	exist[w]=0;
 for(top=bottom;top->next!=NULL;top=top->next);
}
void move_to_top(char w){
	if(top->c==w)return;
	for(ptr=bottom;ptr!=NULL && ptr->c!=w;last=ptr,ptr=ptr->next);
	top->next=ptr;
	if(ptr==bottom)bottom=bottom->next;
	else last->next=ptr->next;
	ptr->next=NULL;
	top=ptr;
}
void move_to_bottom(char w){
	if(bottom->next->c==w)return;
	for(ptr=bottom;ptr!=NULL && ptr->c!=w;last=ptr,ptr=ptr->next);
	last->next=ptr->next;
	ptr->next=bottom->next;
	bottom->next=ptr;
 	for(top=bottom;top->next!=NULL;top=top->next);
}
int use[10000];
void show(char w){
	if(top->c==w){
		puts("100.000");
		return;
	}
int i,co,sx,sy,ex,ey,jx,jy,kx,ky,rn=1,num1,num2,orn;
	for(i=0;i<10000;i++)use[i]=1;
	rn=1,ptr=bottom->next;
	if(ptr->c==w)
		num1=(ptr->ex-ptr->sx+1)*(ptr->ey-ptr->sy+1);
	rect[0]=__rect(ptr->c,ptr->sx,ptr->sy,ptr->ex,ptr->ey);
	while((ptr=ptr->next)!=NULL){
		jx=ptr->sx,jy=ptr->sy;
		kx=ptr->ex,ky=ptr->ey;
		if(ptr->c==w)num1=(kx-jx+1)*(ky-jy+1);
		for(orn=rn,co=i=0;i<orn;i++,co=0){
			if(!use[i])continue;
			sx=rect[i].sx,sy=rect[i].sy;
			ex=rect[i].ex,ey=rect[i].ey;
			if(sx>kx || sy>ky || ex<jx || ey<jy)continue;
			a=__rect(rect[i].c,sx,sy,kx<?(ex),jy-1);
			b=__rect(rect[i].c,sx,jy>?(sy),jx-1,ey);
			c=__rect(rect[i].c,jx>?(sx),ky+1,ex,ey);
			d=__rect(rect[i].c,kx+1,sy,ex,ky<?(ey));
			if(a.sx>=sx && a.sy>=sy && a.ex<=ex && a.ey<=ey &&
			a.sx<=a.ex && a.sy<=a.ey){
				rect[rn++]=a;
				co=1;
			}
			if(b.sx>=sx && b.sy>=sy && b.ex<=ex && b.ey<=ey &&
			b.sx<=b.ex && b.sy<=b.ey){
				rect[rn++]=b;
				co=1;
			}
			if(c.sx>=sx && c.sy>=sy && c.ex<=ex && c.ey<=ey &&
			c.sx<=c.ex && c.sy<=c.ey){
				rect[rn++]=c;
				co=1;
			}
			if(d.sx>=sx && d.sy>=sy && d.ex<=ex && d.ey<=ey &&
			d.sx<=d.ex && d.sy<=d.ey){
				rect[rn++]=d;
				co=1;
			}
			if(co || (jx<=sx && jy<=sy && kx>=ex && ky>=ey))use[i]=0;
		}
		rect[rn++]=__rect(ptr->c,jx,jy,kx,ky);
	}
	for(num2=i=0;i<rn;i++)
		if(rect[i].c==w && use[i])
		    num2+=(rect[i].ex-rect[i].sx+1)*(rect[i].ey-rect[i].sy+1);
	printf("%.3lf\n",double(num2)/double(num1)*100);
}
