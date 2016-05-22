#include<cstdio>
const char digi[]="%[0123456789]",op[]="%[+-*/\n)]";
main()
{
    while(scanf("%d %d %d %d",c,c+1,c+2,c+3) && c[0]+c[1]+c[2]+c[3])
    {
        c['+']=c[0],c['-']=c[1],c['*']=c[2],c['/']=c[3];
        c['\n']=c[')']=-1;
        printf("%d\n",go());
    }
}
