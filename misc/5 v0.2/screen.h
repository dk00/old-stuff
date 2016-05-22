//screen.h
#ifndef SCREEN_H5
#define SCREEN_H5
#include<cstdio>
#include<cstdarg>
int white,black,grey,green,red,yellow;
class Screen
{
    short n,mh,mw,bl,gl,stx,sty;
    char *map[15];
    BITMAP *board,*sp[6];
    void line(int x1,int y1,int x2,int y2,int c)
    {
        ::line(board,y1,x1,y2,x2,c);
    }
    void rect(int x1,int y1,int x2,int y2,int c)
    {
        ::rect(screen,y1,x1,y2,x2,c);
    }
    void grp_init()
    {
        int i,j;
        black=  makecol(0,0,0);
        white=  makecol(255,255,255);
        grey=   makecol(192,192,192);
        green=  makecol(0,255,0);
        red=    makecol(255,0,0);
        yellow= makecol(255,255,0);
        for(i=0;i<6;i++)
            sp[i]=create_bitmap(gl-1,gl-1);
        for(i=0;i<3;i++)
            clear_to_color(sp[i],white);
        for(i=3;i<6;i++)
            clear_to_color(sp[i],grey);
        j=gl*3/7;
        circlefill(sp[1],gl/2-1,gl/2-1,j,black);
        circlefill(sp[2],gl/2-1,gl/2-1,j,white);
        circle(sp[2],gl/2-1,gl/2-1,j,black);
        circlefill(sp[4],gl/2-1,gl/2-1,j,black);
        circlefill(sp[5],gl/2-1,gl/2-1,j,white);
        circle(sp[5],gl/2-1,gl/2-1,j,black);
    }
public:
    void print(int x,int y,char *s, ...)
    {
	   va_list arg;
	   char result[300];
	   va_start(arg,s);
	   vsprintf(result,s,arg);
	   va_end(arg);
	   ::textprintf_ex(screen,font,y,x,black,white,result);
    }
    short fx,fy;
    Screen(short x=800,short y=600):mw(x),mh(y)
    {
        n=15,bl=541,gl=(bl-1)/n;
        stx=(mh-bl)/2,sty=(mw-bl)/2;
        set_gfx_mode(GFX_AUTODETECT_WINDOWED,mw,mh,0,0);
        grp_init();
        clear_to_color(screen,white);
        board=create_sub_bitmap(screen,sty,stx,bl,bl);
        drawboard();
        fx=fy=0;
    }
    void draw(int x,int y)
    {
        draw_sprite(board,sp[map[x][y]],1+gl*y,1+gl*x);
    }
    void drawboard()
    {
        int i;
        for(i=0;i<=n;i++)
        {
            line(i*gl,0,i*gl,bl-1,black);
            line(0,i*gl,bl-1,i*gl,black);
        }
        for(i=0;i<11;i++)
            rect(100+30*i,0,130+30*i,100,black);
        rect(60,700,100,799,black);
        rect(100,700,140,799,black);
    }
    void showcur(int x=mouse_y,int y=mouse_x)
    {
        x=(x-stx)/gl,y=(y-sty)/gl;
        if(!vl(x,y))return;
        if(x!=fx || y!=fy)
        {
            draw_sprite(board,sp[map[fx][fy]],1+gl*fy,1+gl*fx);
            draw_sprite(board,sp[map[x][y]+3],1+gl*y,1+gl*x);
        }
        fx=x,fy=y;
        print(20,130,"(%2d,%2d)%2d",fx,fy,map[fx][fy]);
    }
    void setmap(char s[15][15])
    {
        for(int i=0;i<15;i++)
            map[i]=s[i];
    }
    void mark(int x,int y){floodfill(screen,y,x,grey);}
    void unmark(int x,int y){floodfill(screen,y,x,white);}
    void mark(xlist *s,int c=green)
    {
        for(int i=0;i<s->n;i++)
            floodfill(board,1+gl*((*s)[i].y),1+gl*((*s)[i].x),c);
    }
    void unmark(xlist *s)
    {
        for(int i=0;i<s->n;i++)
            floodfill(board,1+gl*((*s)[i].y),1+gl*((*s)[i].x),white);
    }
    void notice(int x,int y,int& c)
    {
        int i,j;
        x=x*gl+1,y=y*gl+1;
        for(i=0;i<4;i++)
        {
            floodfill(board,y,x,c);
            for(j=clock()+20;j>=clock(););
            floodfill(board,y,x,white);
            for(j=clock()+20;j>=clock(););
        }
    }
};
#endif

