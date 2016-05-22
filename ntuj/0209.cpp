#include<cstdio>
main()
{
    char tmp[9];
    while(scanf("%c",tmp)==1 && tmp[0]!='#')
    {
        if(tmp[0]==' ')printf("%%20");
        else if(tmp[0]=='!')printf("%%21");
        else if(tmp[0]=='$')printf("%%24");
        else if(tmp[0]=='%')printf("%%25");
        else if(tmp[0]=='(')printf("%%28");
        else if(tmp[0]==')')printf("%%29");
        else if(tmp[0]=='*')printf("%%2a");
        else putchar(tmp[0]);
    }
}
