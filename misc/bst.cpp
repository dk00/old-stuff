#include<cstdio>
#include<cstring>
#include"avlt.h"
main()
{
    bst<int> test;
    char cmd[1000];
    int i;
    while(1)
    {
        scanf("%s",cmd);
        if(!strcmp(cmd,"q"))
            break;
        if(!strcmp(cmd,"s"))
        {
            test.show();
            puts("");
            continue;
        }
        scanf("%d",&i);
        if(!strcmp(cmd,"f"))
        {
            printf("%d\n",test.nth(i));
        }
        if(!strcmp(cmd,"i"))
        {
            if(!test.find(i))
                test.ins(i);
        }
        if(!strcmp(cmd,"d"))
        {
            if(test.find(i))
                test.del(i);
        }
    }
}
