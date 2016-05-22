#include<cstdio>
#include<algorithm>
struct dlink
{
    int n,f,add,num;
    dlink *prev,*next;
}*head,*top,*s3[300000],*s[300000];
dlink *add(int n,int f,int num)
{
    if(head==NULL)
    {
        head=top=new dlink;
        head->prev=NULL;
    }
    else top->next=new dlink,top->next->prev=top,top=top->next;
    top->n=n,top->f=n-1,top->num=num;
    top->add=0,top->next=NULL;
    return top;
}
void step(dlink *ptr,dlink *to)
{
    if(head==ptr)
        head=head->next;
    if(ptr->next)
    {
        ptr->next->prev=ptr->prev;
        ptr->next->add+=ptr->add-1;
    }
    if(ptr->prev)
        ptr->prev->next=ptr->next;
    if(to==head)head=ptr;
    ptr->next=to;
    ptr->prev=to->prev,to->prev=ptr;
    if(ptr->prev)ptr->prev->next=ptr;
    ptr->add=0,to->add++;
    ptr->f=to->f;
}
char q1[50000][2];
int n0,n,tmp[300000],s1[50000],s2[50000],q2[50000];
int find(int v)
{
    int i,j,k;
    for(i=0,j=n0-1;i<=j;)
    {
        k=(i+j)/2;
        if(v==tmp[k])return k;
        if(v<tmp[k])j=k-1;
        else i=k+1;
    }
}
int findp(int u)
{
    int i,j,k;
    for(i=1,j=n-1;i<=j;)
    {
        k=(i+j)/2;
        if(s3[k-1]->f+1<u && s3[k]->f+1>=u)
            break;
        if(s3[k]->f+1<u)i=k+1;
        else j=k-1;
    }
    return s3[k]->n+s3[k]->num-u;
}
void print()
{
    dlink *ptr;
    for(ptr=head;ptr;ptr=ptr->next)
        printf("%d-%d ",ptr->n,ptr->n+ptr->num-1);
    puts("");
}
main()
{
    int i,j,k,n1,q;
    dlink *ptr;
    scanf("%d",&n1);
    for(i=0;i<n1;i++)
        scanf("%d %d",&s1[i],&s2[i]);
    scanf("%d",&q);
    for(i=0;i<q;i++)
        scanf("%s %d",q1[i],&q2[i]);
    for(i=j=0;i<n1;i++)
        tmp[j++]=s1[i],tmp[j++]=s2[i];
    for(i=0;i<q;i++)
        if(q1[i][0]=='L')
            tmp[j++]=q2[i];
    std::sort(tmp,tmp+j);
    for(i=n=0;i<j;i++)
        if(!i || tmp[i]!=tmp[i-1])
            tmp[n++]=tmp[i];
    for(n0=n,i=j=0;i<n;i++)
    {
        if(i && tmp[i]-tmp[i-1]>1)
            s3[j++]=add(tmp[i-1]+1,tmp[i-1],tmp[i]-tmp[i-1]-1);
        s3[j++]=s[i]=add(tmp[i],tmp[i]-1,1);
    }
    print();
    for(i=0;i<n1;i++)
        step(s[find(s1[i])],s[find(s2[i])]),print();
    for(n=j,ptr=head;ptr;ptr=ptr->next)
    {
        if(ptr->next)
            ptr->next->add+=ptr->add;
        ptr->f+=ptr->add;
    }
    for(i=0;i<q;i++)
        if(q1[i][0]=='P')
            printf("%d\n",s[q2[i]]->f+1);
        else
            printf("%d\n",findp(q2[i]));
    scanf(" ");
}
