class screen
{
    void *con$;
    short cx,cy,mx,my;
public:
    screen();
    short color(short c=-1);
    int getloc(short,short);
    int setloc(short);
    int inkey();
    int waitkey();
    int printf(short,short,short,const char[],...);
    int printf(short,short,const char[],...);
    int printf(short,const char[],...);
};
enum {Back=8,Tab=9,Enter=13,Esc=27,Spc=32,Up=328,Left=331,Right=333,
Down=336,Del=339,PgUp=329,PgDn=337};
