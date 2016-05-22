#include<cstdio>
#include<algorithm>
main()
{
    int i,T,s[4];
    scanf("%d",&T);
    while(T--)
    {
        for(i=0;i<4;i++)
            scanf("%d",s+i);
        std::sort(s,s+4);
        if(s[0]==s[1] && s[2]==s[3])
        {
            if(s[1]==s[2])
                puts("square");
            else
                puts("rectangle");
        }
        else if(0ll+s[0]+s[1]+s[2]>=s[3])
            puts("quadrangle");
        else
            puts("banana");
    }
}
