typedef struct _
{
    int c,n,k;
    struct _ *l,*r;
}node;
node *root;
void ins(int p,int c,int k)
{
    node **ptr;
    for(ptr=&root;*ptr;)
    {
        if(p<=(*ptr)->n)(*ptr)->n+=k,ptr=&(*ptr)->l;
        else if(p<(*ptr)->n+(*ptr)->k)
        {
            p-=(*ptr)->n;
            node *tmp=malloc(sizeof(*tmp));
            *tmp=**ptr;
            tmp->r=0;
            tmp->k=p;
            (*ptr)->l=tmp;
            tmp=malloc(sizeof(*tmp));
            *tmp=**ptr;
            tmp->l=0;
            tmp->n=0;
            tmp->k=(*ptr)->k-p;
            (*ptr)->r=tmp;
            (*ptr)->c=c;
            (*ptr)->k=k;
            (*ptr)->n=(*ptr)->l->n+(*ptr)->l->k;
            return;
        }
        else p-=(*ptr)->n+(*ptr)->k,ptr=&(*ptr)->r;
    }
    *ptr=malloc(sizeof(**ptr));
    (*ptr)->l=(*ptr)->r=0;
    (*ptr)->c=c;
    (*ptr)->n=0;
    (*ptr)->k=k;
}
void printx(node *ptr)
{
    if(!ptr)return;
    putchar('(');
    printx(ptr->l);
    putchar(')');
    printf("%c%d",ptr->c,ptr->k);
    putchar('(');
    printx(ptr->r);
    putchar(')');
}
int la,lb;
void print(int a,int b)
{
    if(a!=la)
    {
        if(la>0 && lb>0)printf("%c %d ",la,lb);
        la=a,lb=b;
    }
    else lb+=b;
}
void printres(node *ptr)
{
    if(!ptr)return;
    printres(ptr->l);
    print(ptr->c,ptr->k);
    printres(ptr->r);
}
main()
{
    int i,k,n=0;
    char tmp[99],cmd[99];
    while(scanf("%s",cmd)==1)
    {
        if(cmd[0]=='p')
        {
            printres(root);
            print(0,0);
            puts("$");
            continue;
        }
        scanf("%s",tmp);
        if(sscanf(tmp,"%d",&i)==0)
            i=(tmp[0]=='l')?1:n+1;
        scanf("%s",tmp);
        scanf("%d",&k);
        if(k==0)continue;
        ins(i-1,tmp[0],k);
        n+=k;
    }
}
