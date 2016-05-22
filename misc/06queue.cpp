#include<cstdio>
#include<algorithm>
struct dlink
{
    int f,n,add,num;
    dlink *prev,*next;
}*head=NULL,*top=NULL,*s[150000];
dlink *add(int n,int num)
{
    if(head==NULL)
    {
        head=top=new dlink;
        head->prev=NULL;
    }
    else
        top->next=new dlink,top->next->prev=top,top=top->next;
    top->n=n,top->f=n-1,top->add=0;
    top->num=num,top->next=NULL;
    return top;
}
void step(dlink *ptr,dlink *to)
{
    if(ptr->next)
    {
        ptr->next->add-=ptr->add+1;
        ptr->next->prev=ptr->prev;
    }
    if(ptr->prev)
        ptr->prev->next=ptr->next;
    ptr->next=to,ptr->prev=to->prev;
    if(ptr->prev)
        ptr->prev->next=ptr;
    to->prev=ptr,to->add++;
    if(ptr->prev)
        ptr->f=ptr->prev->f+1;
    else if(ptr->next)
        ptr->f=ptr->next->f;
}
int n,s1[50000],s2[50000],q2[50000],tmp[150000];
char q1[50000][2];
int find(int v)
{
    int i,j,k;
    for(i=0,j=n-1;i<=j;)
    {
        k=(i+j)/2;
        if(tmp[k]==v)return k;
        if(tmp[k]<v)i=k+1;
        else j=k-1;
    }
}
main()
{
    int i,j,n1,q,a,b;
    dlink *ptr;
    scanf("%d",&n1);
    for(i=0;i<n1;i++)
        scanf("%d %d",&s1[i],&s2[i]);
    scanf("%d",&q);
    for(i=0;i<q;i++)
        scanf("%s %d",q1[i],&q2[i]);
    for(i=n=0;i<n1;i++)
        tmp[n++]=s1[i],tmp[n++]=s2[i];
    for(i=0;i<q;i++)
        tmp[n++]=q2[i];
    std::sort(tmp,tmp+n);
    for(i=j=0;i<n;i++)
        if(!i || tmp[i]!=tmp[i-1])
            tmp[j++]=tmp[i];
    for(n=j,i=j=0;i<n;i++)
    {
        if(i && tmp[i]-tmp[i-1]>1)
            s[j++]=add(tmp[i]+1,tmp[i]-tmp[i-1]-1);
        s[j++]=add(tmp[i],1);
    }
    for(i=0;i<n1;i++)
    {
        a=find(s1[i]),b=find(s2[i]);
        step(s[a],s[b]);
    }
    for(ptr=head;ptr;ptr=ptr->next)
    {
        ptr->f+=ptr->add;
        if(ptr->next)ptr->next->add+=ptr->add;
    }
    for(i=0;i<q;i++)
    {
        if(q1[0]=='L')
            printf("%d\n",s[q2[i]]->f+1);
        else
            printf("%d\n",findp(q2[i]));
        
    }
    puts("");
    scanf(" ");
}
