#include"maptype.h"
typedef struct _
{
    struct _ *ne,*ch;
    char key;
    VALUE *val;
}node;

node *go(node **ptr,char x[],int n,char build)
{
    while(*ptr && x[0]!=(*ptr)->key)
        ptr=&(*ptr)->ne;
    if(!*ptr)
    {
        if(!build)return 0;
        *ptr=malloc(sizeof(**ptr));
        (*ptr)->ne=(*ptr)->ch=0;
        (*ptr)->val=0;
        (*ptr)->key=x[0];
    }
    if(n==1)
    {
        if(build && (*ptr)->val)
            free((*ptr)->val);
        return *ptr;
    }
    if(x[0]==(*ptr)->key)
        return go(&(*ptr)->ch,x+1,n-1,build);
}

typedef struct Map{
    int n;
    node *root;
}MAP;


void init(MAP *s){s->root=s->n=0;}

int map(MAP *s,KEY key,VALUE *val)
{
    char x[sizeof(key)];
    memcpy(x,&key,sizeof(key));
    node *ptr=go(&s->root,x,sizeof(key),0);
    if(!ptr  || !ptr->val)return -1;
    *val=*(ptr->val);
    return 0;
}

int associate(MAP *s,KEY key,VALUE val)
{
    VALUE tmp;
    if(map(s,key,&tmp)==-1 && s->n+1>MAPSIZE)
        return -1;
    char x[sizeof(key)];
    memcpy(x,&key,sizeof(key));
    VALUE *ptr=malloc(sizeof(val));
    *ptr=val;
    go(&s->root,x,sizeof(key),1)->val=ptr;
    s->n++;
    return 0;
}



int isEmpty(MAP *s){return !s->n;}
