#include<window$.h>
main()
{
    int i,j;
    coninit();
    for(i=0;i<16;i++)
        for(j=0;j<16;j++)
            printf(i,j,i*16+j,"o");
    int c,lc=-2;
    while(1)
    {
        c=inkey();
        if(c!=lc)
        {
            printf(1,30,10,"%3d",c);
            if(c>=0)
                printf(2,30,10,"Last Key: %3d",c);
        }
        lc=c;
        if(c==Esc)break;
    }
}
