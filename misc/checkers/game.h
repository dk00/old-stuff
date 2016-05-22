#ifndef chk_game_h
#define chk_game_h
class board
{
    void ins(char,char,char,char u=0);
    void del(char,char,char u=0);
    int p[200],step,f;
    char act[1000],cl[1000],px[1000],py[1000];
public:
    char s[8][8],t[8][8][4],num[2],at[2],pl,grp;
    void reset();
    char move(char,char,char);
    void undo();
    void show(char,char,char l=0);
    void draw(char,char,char l=0);
    inline char active(char x,char y)
    {   char tmp=!!at[s[x][y]%2];
        return(t[x][y][0]>tmp || t[x][y][1]>tmp || t[x][y][2]>tmp || t[x][y][3]>tmp);}
};
#endif
