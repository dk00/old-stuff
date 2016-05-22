#include<cstdio>
main()
{
    char s[1000],c;
    int d=0,j;
    while(gets(s))
    {
        sscanf(s," %c",&c);
        if(c=='{')d++;
        else if(c=='}')d--;
        else if(d>0)
            printf("    ");
        for(j=0;s[j]==' ';j++);
        if(j%4==3)
            putchar(' ');
        puts(s);
    }
}
