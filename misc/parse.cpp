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
    int c;
    while((c=getchar())!=EOF)
    {
        if(c=='<')
        {
            if(nextchar()=='/')
                putchar(']');
            else
                putchar('[');
            read('>');
            
        }
        else
            putchar(c);
    }
}
/*
[
  [][][[001]][��ǳǪǼ��(Bulbasaur)]
]
[[[��]]]
[[[�r]]]
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
