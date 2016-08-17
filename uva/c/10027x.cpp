#include<stdio.h>
#include<string.h>
struct node
{
    node *c[52];
    char *end;
}*root;
void build(node *&now,char *a,char *b)
{
    if(!now)
    {
        now=new node;
        for(int i=0;i<52;i++)
            now->c[n]=NULL;
    }
    if(*a)
        build(now->c[*a],a+1,b);
    else now->end=b;
    
}
int n,sum;
char s1[100][11],s2[100][11];
main()
{
    int t;
    char *ptr,st[1000],tmp[1000];
    for(n='A';n<='Z';n++)
        to[n]=n-'A';
    for(n='a';n<='z';n++)
        to[n]=n-'a'+26;
    scanf("%d%c",&t,tmp);
    gets(tmp);
    while(t--)
    {
        gets(tmp);
        ptr=strtok(tmp,"\"");
        sscanf(ptr,"%s",st);
        for(n=sum=0;gets(tmp) && tmp[0];n++)
        {
            ptr=strtok(tmp,"\"");
            sscanf(ptr,"%s",s1[n]);
            ptr=strtok(0,"\"");
            ptr=strtok(0,"\"");
            sscanf(ptr,"%s",s2[n]);
            build(root,s1,s2);
        }
        go(st);
        if(sum<=1000)
            printf("%d\n",sum);
        else
            puts("Too many");
        if(t)puts("");
    }
}
