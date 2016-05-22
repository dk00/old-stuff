#include<cstdio>
struct node
{
    node *c[7],*sub;
    int b,cc;
}*root;
void build(node *&ptr,char *a,int b,int cc)
{
    if(ptr==NULL)
    {
        ptr=new node;
        for(int i=0;i<7;i++)
            ptr->c[i]=0;
        ptr->b=-1;
        ptr->cc=cc;
        ptr->sub=0;
    }
    if(a[0])
    {
        build(ptr->c[a[0]-'1'],a+1,b,cc+1);
        return;
    }
    if(ptr->b==-1)
        ptr->b=b;
}
void link(char *a)
{
    int i,j,n;
    node *ptr1[300],*ptr2[300];
    for(n=0;a[n];n++)
    {
        ptr1[n]=root->c[a[n]-'1'];
        ptr2[n]=root;
        ptr1[n]->sub=ptr2[n];
    }
    for(i=0;i<n;i++)
        for(j=1;i+j<n;j++)
        {
            ptr1[i]=ptr1[i]->c[a[i+j]-'1'];
            while(ptr2[i]!=root && !ptr2[i]->c[a[i+j]-'1'])
                ptr2[i]=ptr2[i]->sub;
            if(ptr2[i]->c[a[i+j]-'1'])
                ptr2[i]=ptr2[i]->c[a[i+j]-'1'];
            ptr1[i]->sub=ptr2[i];
            if(ptr1[i]->b==-1)
                ptr1[i]->b=ptr2[i]->b;
        }
}
char p[1000],s[1200][1200];
main()
{
    int i,j,n,maxb,maxc;
    maxb=maxc=0;
    node *ptr;
    root=NULL;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%s",s[i]);
    scanf("%s",p);
    for(i=0;p[i];i++)
        build(root,p+i,0,0);
    link(p);
    for(i=0;i<n;i++)
    {
        ptr=root;
        for(j=0;s[i][j];j++)
        {
            while(ptr!=root && !ptr->c[s[i][j]-'1'])
                ptr=ptr->sub;
            if(ptr->c[s[i][j]-'1'])
                ptr=ptr->c[s[i][j]-'1'];
            if(ptr->cc>maxc)
                maxb=i,maxc=ptr->cc;
        }
    }
    printf("%d %d\n",maxb+1,maxc);
}
