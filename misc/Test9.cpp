#include<ctime>
#include<cstdio>
#include<cstdlib>
char s0[]=".:*       ",s1[]="¡G¡ï¡E£»¡K¡L¡î¡D¡O¡P¡R        ";
main()
{
    char c[100];
    int i,j;
    srand(time(NULL));
    //while(1)
    //{
        for(i=0;i<2000;i++)
            if(rand()>(32767*85/100))
            {
                j=rand()%15;
                if(j<3)
                    putchar(s0[j]);
                else printf("%c%c",s1[(j-3)*2],s1[(j-3)*2+1]);
            }
            else putchar(' ');
      //  gets(c);
    //}
}
