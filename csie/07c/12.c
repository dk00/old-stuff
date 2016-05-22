typedef struct 
{
    char c;
    struct list *next;
}list;
int n;
list *q;
list **seek(int k)
{
    list **ptr;
    for(ptr=&q;k--;ptr=&((*ptr)->next));
    return ptr;
}
void ins(int k,char c)
{
    if(k<0 || k>n)return;
    n++;
    list **ptr=seek(k),*x;
    x=malloc(sizeof(list));
    x->next=(*ptr);
    *ptr=x;
    x->c=c;
}
void del(int k)
{
    if(k<0 || k>=n)return;
    n--;
    list **ptr=seek(k),*tmp=(*ptr)->next;
    free(*ptr);
    *ptr=tmp;
}
void print()
{
    list *ptr;
    for(ptr=q;ptr;ptr=ptr->next)
        putchar(ptr->c);
}
int n0,s0[20000];
main()
{
    int i,j,k,l;
    list *ptr;
    char cmd[99],tmp[99];
    n=0;
    q=malloc(sizeof(list));
    q->c='\n';
    q->next=0;
    while(scanf("%s",cmd)==1)
    {
        scanf("%s",tmp);
        if(tmp[0]=='l')i=1;
        else if(tmp[0]=='r')i=n+(cmd[0]=='i');
        else sscanf(tmp,"%d",&i);
        if(cmd[0]=='i')
        {
            scanf("%s",tmp);
            ins(i-1,tmp[0]);
        }
        else
            del(i-1);
        //print();
    }
    for(i=j=n0=0,k=-1,ptr=q;ptr->next;ptr=ptr->next)
    {
        if(ptr->c==k)++i;
        else i=1;
        k=ptr->c;
        if(i>j)j=i,n0=1,s0[0]=k;
        else if(i==j)s0[n0++]=k;
    }
    for(i=0;i<n0;i++)
        printf("%c ",s0[i]);
    printf("%d\n",j);
}
