#include<cstdio>
#include<cstring>
struct node
{
    node *c[52];
    int end;
}*root=0,*ann;
char s1[100][11],s2[100][11],len[100];
int to[256],next[100],path[100],use[100];
int n,sum;
int build(node *&now,char *a,int b)
{
    int _s=0;
    if(!now)
    {
        now=new node;
        now->end=-1;
        for(int i=0;i<52;i++)
            now->c[i]=NULL;
        _s=1;
    }
    if(*a)
        return build(now->c[to[*a]],a+1,b);
    int *i;
    for(i=&now->end;b>=0 && *i!=-1;i=&next[*i]);
    *i=b;
    return _s;
}
void go(int d,char s0[])
{
    if(sum++>=1000)
        return;
    char tmp[1050];
    node *ptr;
    int i,j;
    for(i=0;s0[i];i++)
    {
        for(j=i,ptr=root;ptr && (!j || s0[j-1]);ptr=ptr->c[to[s0[j++]]])
        {
            for(int k=ptr->end;k!=-1;k=next[k])
            {
                strcpy(tmp+i,s2[k]);
                strcpy(tmp+i+len[k],s0+j);
                if(build(ann,tmp,-1))
                    go(d+1,tmp);
            }
        }
        tmp[i]=s0[i];
    }
}
void clear(node **ptr)
{
    if(*ptr==NULL)
        return;
    for(int i=0;i<52;i++)
        if((*ptr)->c[i])clear(&(*ptr)->c[i]);
    delete *ptr;
    *ptr=NULL;
}
main()
{
    int t;
    char *ptr,st[1000],tmp[1000];
    root=ann=NULL;
    for(n='A';n<='Z';n++)
        to[n]=n-'A';
    for(n='a';n<='z';n++)
        to[n]=n-'a'+26;
    scanf("%d%c",&t,tmp);
    gets(tmp);
    while(t--)
    {
        clear(&root),clear(&ann);
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
            len[n]=strlen(s2[n]);
            use[n]=0;next[n]=-1;
            build(root,s1[n],n);
        }
        path[0]=-1;
        go(1,st);
        if(sum<=1000)
            printf("%d\n",sum);
        else
            puts("Too many");
        if(t)puts("");
    }
}
