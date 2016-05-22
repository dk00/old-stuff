#include<cstdio>
#include<conio.h>
#include<windows.h>
main()
{
    void *con;
    con=GetStdHandle(STD_OUTPUT_HANDLE);
    short i,key[10];
    for(i=0;i<10;i++)key[i]=0;
    while(key[9]!=27)
    {
//        if(kbhit())
        for(i=0;i<9;i++)
            key[i]=key[i+1];
        {
            key[9]=getch();
            if(key[9]==0)key[9]=128+getch();
            if(key[9]==224)key[9]=256+getch();
        }
        SetConsoleCursorPosition(con,(COORD){1,0});
        for(i=0;i<10;i++)
            printf("%3d ",key[i]);
    }
}
