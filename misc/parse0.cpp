#include<cstdio>
void read(char x)
{
    int c;
    while((c=getchar())!=EOF && c!=x);
}
char nextchar()
{
    int c=getchar();
    if(c!=EOF)ungetc(c,stdin);
    return c;
}
main()
{
    int c,i=0;
    while((c=getchar())!=EOF)
    {
        if(c=='[')
        {
            while(nextchar()=='[')getchar();
            if(nextchar()==']')
                printf(" 0 ");
            else
                while(nextchar()!=']')
                    putchar(getchar());
            while(nextchar()==']')getchar();
            if(i++%20==19)puts("");
            putchar(' ');
        }
    }
}
/*
[
  [][][[001]][ÇÑÇ³ÇªÇ¼ÇÉ(Bulbasaur)]
]
[[[¯ó]]]
[[[¬r]]]
[[45]][[49]][[49]][[65]][[65]][[45]][[318]]
[]
[]
[]
[[1]]
[]
[]
[]
]
*/
