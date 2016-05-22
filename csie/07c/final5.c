#include<stdio.h>
int n;
char name[3000][99];
int p1[3000],p2[3000];
typedef struct _
{
    char x;
    int n;
    struct _ *ne,*ch;
}node;
node *root;
int u;
int find(node **ptr,char a[],int x)
{
    while(*ptr && a[0]!=(*ptr)->x)ptr=&(*ptr)->ne;
    if(!*ptr)
    {
        if(!x)return -1;
        *ptr=malloc(sizeof(**ptr));
        (*ptr)->x=a[0];
        (*ptr)->n=-1;
        (*ptr)->ne=(*ptr)->ch=0;
    }
    if(!a[1])
    {
        if(x && (*ptr)->n==-1)
            (*ptr)->n=u++;
        return (*ptr)->n;
    }
    return find(&(*ptr)->ch,a+1,x);
}
main()
{
    int i,j,k;
    for(i=0;i<3000;i++)
        p1[i]=p2[i]=-1;
    char tmp[999],tmp1[999],tmp2[999],tmp3[999];
    while(gets(tmp))
    {
        if(j=sscanf(tmp,"%s %s %s",tmp1,tmp2,tmp3)!=3)break;
        i=find(&root,tmp1,1);
        strcpy(name[i],tmp1);
        j=find(&root,tmp2,1);
        strcpy(name[j],tmp2);
        k=find(&root,tmp3,1);
        strcpy(name[k],tmp3);
        p1[i]=j;
        p2[i]=k;
    }
    while(scanf("%s",tmp)==1)
    {
        for(j=0;tmp[j];j++);
        if(tmp[j-2]=='\'')
            tmp[j-2]=0;
        if(tmp[j-1]=='\'')
            tmp[j-1]=0;
        i=find(&root,tmp,0);
        while(scanf("%s",tmp))
        {
            for(j=0;tmp[j];j++);
            if(i<0)
            {
                if(tmp[j-1]=='r')break;
                continue;
            }
            if(tmp[0]=='f')
                i=p1[i];
            else
                i=p2[i];
            if(tmp[j-1]=='r')break;
        }
        if(i<0)puts("*unknown*");
        else puts(name[i]);
    }
}
