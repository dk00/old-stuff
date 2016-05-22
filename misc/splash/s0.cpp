#include<cstdio>
#include<cstring>
#include"sclass1.h"
P test;
int tmp1[6][6],r[]={0,4,3,2,1};
int calc1(int s[][6])
{
    int i,j,left=-1,top=-1,lx,ly,sum;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            tmp1[i][j]=0;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
        {
            if(s[i][j])
            {
                if(left>0)
                {
                    tmp1[i][j]+=left;
                    tmp1[i][ly]+=s[i][j];
                }
                ly=j;
                left=s[i][j];
            }
            if(s[j][i])
            {
                if(top>0)
                {
                    tmp1[j][i]+=top;
                    tmp1[lx][i]+=s[j][i];
                }
                lx=j;
                top=s[j][i];
            }
        }
    for(i=sum=0;i<6;i++)
    {
        for(j=0;j<6;j++)
            printf("%2d ",tmp1[i][j]*r[s[i][j]]),
            sum+=tmp1[i][j];
        puts("");
    }
    printf("%d\n",sum);
}
main()
{
    char cmd[1000];
    int i,j;
    while(scanf("%s",cmd))
    {
        if(strcmp(cmd,"set")==0)
            test.get();
        else if(strcmp(cmd,"c1")==0)
            calc1(test.s);
        else if(strcmp(cmd,"add")==0)
        {
            scanf("%d %d",&i,&j);
            test.add(i-1,j-1);
        }
        else if(strcmp(cmd,"show")==0)
        {
            for(i=0;i<6;i++)
            {
                for(j=0;j<6;j++)
                    printf("%d ",test.s[i][j]);
                puts("");
            }
        }
    }
}
