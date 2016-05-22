#include<cstdio>
char c,s[2][35],shift[2][35];
main()
{
    int i,j,k;
    gets(s[0]),gets(s[1]);
    for(i=j=k=0;i<32;i++)
    {
        if(s[0][i]==' ')
            shift[0][i]=j++;
        if(s[1][i]==' ')
            shift[1][i]=k++;
    }
    k=0;
    while((c=getchar())!=EOF)
    {
        if(c=='\n')
        {
            k=0,puts("");
            continue;
        }
        for(i=1,j=c-'0';i<5;i++,j=j*2+getchar()-'0');
        if(shift[k][j])
            k=shift[k][j]-1;
        else putchar(s[k][j]);
    }
}
