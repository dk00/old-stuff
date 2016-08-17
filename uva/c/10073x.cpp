#include<cstdio>
#include<cstdlib>
#include<cstring>
int d[]={1,3,6,12},to[12][12]={
{0,1,2,1,2,3,1,2,3,2,3,4},{1,0,1,2,1,2,2,1,2,3,2,3},
{2,1,0,3,2,1,3,2,1,4,3,2},{1,2,3,0,1,2,2,3,4,1,2,3},
{2,1,2,1,0,1,3,2,3,2,1,2},{3,2,1,2,1,0,4,3,2,3,2,1},
{1,2,3,2,3,4,0,1,2,1,2,3},{2,1,2,3,2,3,1,0,1,2,1,2},
{3,2,1,4,3,2,2,1,0,3,2,1},{2,3,4,1,2,3,1,2,3,0,1,2},
{3,2,3,2,1,2,2,1,2,1,0,1},{4,3,2,3,2,1,3,2,1,2,1,0}},
togo[12][6]={{1,3,6,-1,0},{0,2,4,7,-1},{1,5,8,-1,0},{0,4,9,-1,0},
{1,3,5,10,-1},{2,4,11,-1,0},{0,7,9,-1,0},{1,6,8,10,-1},
{2,7,11,-1,0},{3,6,10,-1,0},{4,7,9,11,-1},{5,8,10,-1,0}};
int l1,score,bound,next;
char s[13],path[1000],use[100][13];
bool dfs(int dt)
{
    if(!score)
    {
        path[dt]=0;
        return 1;
    }
    int i=dt+score;
    if(i>bound)
    {
        next<?=i;
        return 0;
    }
    for(i=0;i<dt;i++)
        if(!memcmp(s,use[i],12))
            return 0;
    memcpy(use[dt],s,12);
    int tmp,l2;
    for(i=0;togo[l1][i]>=0;i++)
    {
        l2=togo[l1][i];
        path[dt]=s[l2]+'A';
        score+=to[s[l2]][l1]-to[s[l2]][l2];
        tmp=s[l1],s[l1]=s[l2],s[l2]=tmp;
        tmp=l1,l1=l2,l2=tmp;
        if(dfs(dt+1))
            return 1;
        tmp=l1,l1=l2,l2=tmp;
        tmp=s[l1],s[l1]=s[l2],s[l2]=tmp;
        score-=to[s[l2]][l1]-to[s[l2]][l2];
    }
    return 0;
}
main()
{
    int i,j,k,t,C=1;
    char c[1000];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s",c);
        for(i=score=0;i<12;i++)
        {
            s[i]=c[i]-'A';
            if(c[i]=='L')
            {
                l1=i;
                continue;
            }
            score+=to[s[i]][i];
        }
        next=score;
        do bound=next,next=1000;
        while(!dfs(0));
        printf("Permutation #%d\n",C++);
        puts(path);
        puts("");
    }
}
