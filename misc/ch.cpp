#include<cstdio>
#include<string>
using namespace std;
char c[10][256];
main()
{
    int x,i,j;
    string tmp;
    for(i=0;i<10;i++)
        for(j=0;j<256;j++)
            c[i][j]=9;
    c[0][' ']=0,c[1][' ']=1;
    c[0]['#']=1;
    c[1]['i']=2;
    c[2]['n']=3;
    c[3]['c']=4;
    c[4]['l']=5;
    c[5]['u']=6;
    c[6]['d']=7;
    c[7]['e']=8;
    while((x=getchar())!=EOF)
    {
        j=0;
        tmp="";
        while(x!='\n' && j<8)
        {
            j=c[j][x];
            tmp.push_back(x);
            x=getchar();
        }
        if(j==8)
            while(x!='\n')
                x=getchar();
        else
        {
            printf(tmp.c_str());
            while(x!='\n')
            {
                putchar(x);
                x=getchar();
            }
        }
        puts("");
    }
}
