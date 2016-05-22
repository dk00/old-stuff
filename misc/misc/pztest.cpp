#include<cstdio>
#include<cstdlib>
#define _MSC_VER 1
#include"scrctrl.h"
#include"puzzle.h"
puzzle test,tmp[1000];
int min,bound,rev[]={2,3,0,1};
char dir[]="DRUL",path[1000];
char spc[]="                                                  ";
bool dfs(int d)
{
    if(!test.pnum)
    {
        path[d]=0;
        return true;
    }
    if(d+test.pnum>bound)
    {
        if(min==bound)
            min=d+test.pnum;
        if(min>d+test.pnum)
            min=d+test.pnum;
        return false;
    }
    if(min==bound+1)
        return false;
    /*for(int i=0;i<d;i++)
        if(test==tmp[i])
            return false;*/
    //tmp[d]=test;
    bool found;
    for(int i=0;i<4;i++)
        if(test.move(i))
        {
            path[d]=dir[i];
            found=dfs(d+1);
            test.move(rev[i]);
            if(found)
                return true;
        }
    return false;
}
main()
{
    int c;
    bool solvable=test.get();
    srand(test.calc());
    consoleinit();cls();
    while(1)
    {
        test.show();
        c=inkey();
        if(c==27)
            break;
        if(c==DOWN)test.move(0);
        if(c==RIGHT)test.move(1);
        if(c==UP)test.move(2);
        if(c==LEFT)test.move(3);
        if(c==' ')test.move(rand()%4);
        if(c==13)
        {
            locate(15,10);myputs(spc);
            locate(16,10);myputs(spc);
            if(!solvable)
            {
                locate(15,10);
                myputs("This puzzle is not solvable.");
                continue;
            }
            for(min=bound=test.pnum;;bound=min)
            {
                locate(15,10);
                myputs("Searching... bound:%3d",bound);
                if(dfs(0))break;
            }
            locate(15,10);myputs(spc);
            locate(15,10);myputs("Searching... done.       ");
            locate(16,10);myputs(spc);
            locate(16,10);myputs("Solution: %s",path);
        }
    }
}
