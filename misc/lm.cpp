#include<cmath>
#include<cstdio>
#include<cstdlib>
#include"window$.h"
main()
{
    char tmp[99];
    double l;
    while(scanf("%s %lf",tmp,&l))
    {
        freopen("limit_check.cpp","w",stdout);
        puts("#include<cmath>");
        puts("#include<cstdio>");
        puts("double f(double x)");
        puts("{");
        printf("    return %s;\n",tmp);
        puts("}");
        puts("main()");
        puts("{");
        puts("    int i;");
        puts("    double x;");
        puts("    for(i=0,x=1;i<12;i++,x/=10)");
        printf("        printf(\"%%lf\\n\",f(%lf-x));\n",l);
        puts("    for(i=0;i<12;i++,x*=10)");
        printf("        printf(\"%%lf\\n\",f(%lf+x));\n",l);
        puts("}");
        fclose(stdout);
        system("g++ limit_check.cpp -o lch");
        freopen("CON","w",stdout);
        Run("lch",1);
        freopen("CON","r",stdin);
    }
}
