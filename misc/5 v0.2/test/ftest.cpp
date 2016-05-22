#include<allegro.h>
int main()
{
    allegro_init();
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0);
    install_mouse();
    FONT *myfont;
    PALETTE palette;
    myfont = load_font("cnew.pcx",NULL, NULL);
    if(!myfont)
        allegro_message("Couldn't load font!");
    else
    textout_centre_ex(screen,myfont,"This is my own pretty font!",
    400,300,makecol(0,0,0),makecol(255,255,255));
    while(!mouse_b);
}
END_OF_MAIN()
