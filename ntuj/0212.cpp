#include<cstdio>
#include<cstring>
char c[256][256],res[256][256],test[99]="";
void add(char e[],char r[])
{
    int i,j;
    for(i=0;e[i];i++)
        for(j=0;r[j];j++)
            c[e[i]][r[j]]=1;
}
void sub(char e[],char r[])
{
    int i,j;
    for(i=0;e[i];i++)
        for(j=0;r[j];j++)
            c[e[i]][r[j]]=0;
}
void assign(char e[],char r[])
{
    int i,j;
    for(i=0;e[i];i++)
    {
        for(j=0;j<128;j++)
            c[e[i]][j]=0;
        for(j=0;r[j];j++)
            c[e[i]][r[j]]=1;
    }
}
void gen(int x,char res[])
{
    int i,n=0;
    for(i='a';i<='z';i++)
        if(c[x][i])
            res[n++]=i;
    res[n]=0;
}
main()
{
    int i,C=1;
    char e[99],r[99],x[99],*last;
    while(1)
    {
        for(i='A';i<='Z';i++)
            for(int j='a';j<='z';j++)
                c[i][j]=0;
        while(1)
        {
            scanf("%[ABCDEFGHIJKLMNOPQRSTUVWXYZ#]",e);
            if(e[0]=='#')return 0;
            scanf("%[+-=]",x);
            scanf("%[qwertyuiopasdfghjklzxcvbnm]",r);
            if(x[0]=='+')
                add(e,r);
            if(x[0]=='-')
                sub(e,r);
            if(x[0]=='=')
                assign(e,r);
            scanf("%c",x);
            if(x[0]=='\n')break;
        }
        for(i='A';i<='Z';i++)
            gen(i,res[i]);
        printf("%d:",C++);
        last=test;
        for(i='A';i<='Z';i++)
        {
            if(!res[i][0])continue;
            if(strcmp(res[i],last))
            {
                printf("%s",last);
                last=res[i];
            }
            putchar(i);
        }
        printf("%s",last);
        puts("");
        
    }
}
