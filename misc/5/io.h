#include<allegro.h>
void init()
{
    readcfg();
    allegro_init();
    install_mouse();
    install_keyboard();
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,mw,mh,0,0);
    setcolor();
    enable_hardware_cursor();
    show_mouse(screen);
    drawboard();
}
void setcolor()
{
    white=makecol(255,255,255);
    black=makecol(0,0,0);
    grey=makecol(223,223,223);
    green=makecol(0,255,0);
    blue[0]=makecol(0,255,255);
    blue[1]=makecol(0,127,255);
    blue[2]=makecol(0,0,255);
    blue[3]=makecol(0,0,255);
    red[0]=makecol(255,255,0);
    red[1]=makecol(255,127,0);
    red[2]=makecol(255,0,0);
    red[3]=makecol(255,0,0);
}
void drawboard()
{
    int n=boardsize;
    stx=(mh-boardlen)/2,
    sty=(mw-boardlen)/2,
    gridlen=(boardlen-1)/n;
    clear_to_color(screen,makecol(255,255,255));
    for(int i=0;i<=n;i++)
    {
        line(screen,sty,stx+i*gridlen,sty+boardlen-1,stx+i*gridlen,0);
        line(screen,sty+i*gridlen,stx,sty+i*gridlen,stx+boardlen-1,0);
    }
}
void mark(int x,int y,int s)
{
    if(x==grx && y==gry && s)
        return;
    floodfill(screen,sty+gry*gridlen+1,stx+grx*gridlen+1,white);
    grx=x,gry=y;
    floodfill(screen,sty+gry*gridlen+1,stx+grx*gridlen+1,grey);
}
void mark1(int x,int y,int col)
{
    floodfill(screen,sty+y*gridlen+1,stx+x*gridlen+1,col);
}
void drawgrid(int c,int x,int y)
{
    int cx=stx+gridlen/2+x*gridlen,cy=sty+gridlen/2+y*gridlen,
        r=gridlen*3/7;
    if(c==0)circlefill(screen,cy,cx,r,white);
    if(c==1)circlefill(screen,cy,cx,r,black);
    if(c==2)
    {
        circlefill(screen,cy,cx,r,white);
        circle(screen,cy,cx,r,black);
    }
}
int ngrx,ngry;
void showinfo()
{
    int n=boardsize;
    ngrx=(mouse_y-stx)/gridlen;
    ngry=(mouse_x-sty)/gridlen;
    textprintf_ex(screen,font,0,0,black,white,
    "(%d,%d) %d %d %d   ",
    grx,gry,map[grx][gry],use[ngrx][ngry],c_score[grx][gry]);
    if(ngrx>=0 && ngrx<n && ngry>=0 && ngry<n)
        mark(ngrx,ngry);
    textprintf_ex(screen,font,0,24,black,white,
    "%5d:%5d  ",sc[0][ns],sc[1][ns]);
}
void show_used()
{
    int i;
    for(i=ns;i<ged[ns];i++)
        mark1(togo[i].x,togo[i].y,green);
    while(key[KEY_Z]);
    for(i=ns;i<ged[ns];i++)
        mark1(togo[i].x,togo[i].y,white);
}
void show_warn()
{
    int i,j;
    for(i=0;i<4;i++)
        for(j=0;j<evil[pl][i].npt();j++)
            mark1(evil[pl][i].s[j].x,evil[pl][i].s[j].y,blue[i]);
    for(i=0;i<4;i++)
        for(j=0;j<evil[!pl][i].npt();j++)
            mark1(evil[!pl][i].s[j].x,evil[!pl][i].s[j].y,red[i]);
    while(key[KEY_X]);
    for(i=0;i<4;i++)
        for(j=0;j<evil[pl][i].npt();j++)
            mark1(evil[pl][i].s[j].x,evil[pl][i].s[j].y,white);
    for(i=0;i<4;i++)
        for(j=0;j<evil[!pl][i].npt();j++)
            mark1(evil[!pl][i].s[j].x,evil[!pl][i].s[j].y,white);
}
int readinput()
{
    textprintf_ex(screen,font,0,8,black,white,"%3d Player%d  ",ns,pl+1);
    clear_keybuf();
    while(!mouse_b && !keypressed())
        showinfo();
    if(key[KEY_Z])      show_used();
    if(key[KEY_X])      show_warn();
    if(key[KEY_S]) {    while(key[KEY_S]);      return Save;}
    if(key[KEY_F5]){    while(key[KEY_F5]);     return NewGame;}
    if(key[KEY_ESC]){   while(key[KEY_ESC]);    return Exit;}
    if(key[KEY_SPACE]){ while(key[KEY_SPACE]);  return Search;}
    if(mouse_b&1
    && ab(ngrx,ngry)){  while(mouse_b&1);       return Put;}
    if(mouse_b&2){      while(mouse_b&2);       return Undo;}
    clear_keybuf();
    return Nothing;
}
void click()
{
    int i;
    textprintf_ex(screen,font,192,0,black,white,
    "Click to continue");
    showinfo();
    while(!mouse_b);
    while(mouse_b);
    textprintf_ex(screen,font,192,0,black,white,
    "                 ");
}
