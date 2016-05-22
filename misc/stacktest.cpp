#include<cstdio>
#include<cstring>
#include"stack.h"
main()
{
    stack<int> test;
    char cmd[1000];
    int i;
    while(scanf("%s",cmd)==1)
    {
        if(strcmp(cmd,"exit")==0)
            break;
        if(strcmp(cmd,"push")==0)
        {
            scanf("%d",&i);
            test.push(i);
            printf("%d pushed.\n",i);
        }
        if(strcmp(cmd,"pop")==0)
        {
            if(test.top==NULL)
                puts("The stack is empty.");
            else
            {
                i=test.pop();
                printf("%d popped.\n",i);
            }
        }
        if(strcmp(cmd,"show")==0)
            test.show();
    }
}
