#include<ctime>
#include<cstdio>
#include"r.h"
#include"io.h"
#include"ai.h"
#include"gamectrl.h"
int main()
{
    int c;
    init();
    setscore();
    newgame();
    for(int i=0;i<10;i++)
        nnode[i]=npv[i]=0;
    if(isai[pl])
    {
        int tmp=search();
        textprintf_ex(screen,font,0,32,black,white,
        "(%3d,%3d)%6d ",Best.x,Best.y,pl);
        put(Best.x,Best.y);
    }
    while((c=readinput())!=-1)
    {
            
        if(c==Undo)
        {
            undo();
            if(isai[pl])
                undo();
        }
        if(c==NewGame)
        {
            newgame();
            for(int i=0;i<10;i++)
                nnode[i]=npv[i]=0;
        }
        if(c==Put)
        {
            put();
            showinfo();
        }
        while(isai[pl] && !win[0] && !win[1])
        {
            int tmp=search();
            textprintf_ex(screen,font,0,32,black,white,
            "(%3d,%3d)%6d ",Best.x,Best.y,tmp);
            put(Best.x,Best.y);
        }
        if(c==Save)
        {
            /*char fname[1000];
            time_t tptr=time(NULL);
            sprintf(fname,"%s.txt",ctime(&tptr));*/
            FILE *rec=fopen("rec.txt","w");
            for(int i=Level;i>=0;i--)
                fprintf(rec,"%d %d\n",nnode[i],npv[i]);
            for(int i=0;i<8;i++,fprintf(rec,"\n"))
            {
                for(int j=evil[i/4][i%4].npt()-1;j>=0;j--)
                    fprintf(rec," %d,%d",evil[i/4][i%4].s[j].x,
                    evil[i/4][i%4].s[j].y);
                for(int j=0;j<225;j++)
                {
                    fprintf(rec," %d",evil[i/4][i%4].num[j/15][j%15]);
                    if(j%15==0)
                        fprintf(rec,"\n");
                }
            }
            for(int i=0;i<ns;i++)
                fprintf(rec,"(%d,%d)\n",move[i].x,move[i].y);
            fclose(rec);
        }
    }
}
END_OF_MAIN()
