// input.h
#ifndef INPUT_H5
#define INPUT_H5
class Input
{
    volatile char *pkey[100];
    int rn,rv[100],flag[100],flag2[15],flag4,flag5;
    Screen *xout;
public:
    xlist **q;
    Input(Screen *x):xout(x)
    {
        install_mouse();
        install_keyboard();
        enable_hardware_cursor();
        show_mouse(screen);
        pkey[0]=new volatile char;
        pkey[1]=new volatile char;
        rv[0]=Put,rv[1]=Undo;
        rn=2;
        regkey(&key[KEY_PGUP],(int)Inc);
        regkey(&key[KEY_PGDN],(int)Dec);
        regkey(&key[KEY_ENTER],(int)Rec);
        regkey(&key[KEY_F5],(int)Newgame);
        regkey(&key[KEY_ESC],(int)Exit);
        regkey(&key[KEY_SPACE],(int)Search);
        flag4=flag5=0;
    }
    ~Input()
    {
        delete pkey[0];
        delete pkey[1];
    }
    int getinput()
    {
        clear_keybuf();
        while(1)
        {
            xout->showcur(mouse_y,mouse_x);
            *pkey[0]=mouse_b&1;
            *pkey[1]=mouse_b&2;
            int i,v,ax=mouse_y,ay=mouse_x;
            for(i=0,v=-1;i<rn;i++)
            {
                if(*pkey[i] && !flag[i])
                    v=i;
                flag[i]=*pkey[i];
            }
            if(v>=0)
            {
                if(rv[v]==Put && 60<ax && ax<140 && 700<ay && ay<799)
                {
                    flag4=flag5=0;
                    return Change;
                }
                return rv[v];
            }
            for(i=0;i<11;i++)
            {
                if(100+30*i<mouse_y &&mouse_y<130+30*i &&
                0<mouse_x && mouse_x<100)
                {
                    if(!flag2[i])
                    flag2[i]=1,
                    xout->mark(101+30*i,1);
                    xout->mark(q[i]);
                }
                else if(flag2[i])
                {
                    flag2[i]=0;
                    xout->unmark(101+30*i,1);
                    xout->unmark(q[i]);
                }
            }
            if(60<ax && ax<100 && 700<ay && ay<799)
            {
                if(!flag4)
                    flag4=1,xout->mark(76,711);
            }
            else if(flag4)
                flag4=0,xout->unmark(76,711);
            if(100<ax && ax<140 && 700<ay && ay<799)
            {
                if(!flag5)
                    flag5=1,xout->mark(116,711);
            }
            else if(flag5)
                flag5=0,xout->unmark(116,711);
        }
        return Exit;
    }
    void regkey(volatile char *s,int retv)
    {
        pkey[rn]=s;
        rv[rn++]=retv;
    }
    void click()
    {
        while(!mouse_b);
        while(mouse_b);
    }
};
#endif
