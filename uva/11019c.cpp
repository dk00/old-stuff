#include<cstdio>
#include<cstring>
struct node
{
    node *sub,*c[26];
    int b;
}*root,*ptr1[100],*ptr2[100];
int to[256],now[1001],next[101],c[101][101];
char s[1000][1001],p[100][101];
void clear(node **ptr)
{
    if(*ptr)
    {
        for(int i=0;i<26;i++)
            clear(&(*ptr)->c[i]);
        delete *ptr;
        *ptr=NULL;
    }
}
int build(node *&ptr,char *a,int b)
{
    if(!ptr)
    {
        ptr=new node;
        for(int i=0;i<26;i++)
            ptr->c[i]=NULL;
        ptr->b=-1;
    }
    if(*a)
        return build(ptr->c[to[*a]],a+1,b);
    if(ptr->b>=0)
        return ptr->b;
    return(ptr->b=b);
}
main()
{
    node *ptr;
    int i,j,n,m,t,sum;
    for(i='a';i<='z';i++)
        to[i]=i-'a';
    scanf("%d",&t);
    while(t--)
    {
        clear(&root);
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            scanf("%s",s[i]);
        scanf("%d %d",&m,&j);
        for(i=0;i<m;i++)
        {
            next[i]=0;
            scanf("%s",p[i]);
            for(j=0;j<=i;j++)
                c[i][j]=c[j][i]=!strcmp(p[i],p[j]);
            j=build(root,p[i],i);
        }
        for(i=1,j=0;i<m;i++)
        {
            while(j>0 && !c[i][j])
                j=next[j];
            j+=c[i][j];
            next[i+1]=j;
        }
        for(i=0;i<m;i++)
        {
            ptr1[i]=root->c[to[p[i][0]]];
            ptr2[i]=root;
            ptr1[i]->sub=ptr2[i];
        }
        for(j=1;p[0][j];j++)
            for(i=0;i<m;i++)
            {
                ptr1[i]=ptr1[i]->c[to[p[i][j]]];
                while(ptr2[i]!=root && !ptr2[i]->c[to[p[i][j]]])
                    ptr2[i]=ptr2[i]->sub;
                if(ptr2[i]->c[to[p[i][j]]])
                    ptr2[i]=ptr2[i]->c[to[p[i][j]]];
                ptr1[i]->sub=ptr2[i];
                if(ptr2[i]->b>0)
                    ptr1[i]->b=ptr2[i]->b;
            }
        for(j=0;s[0][j];j++)
            now[j]=0;
        for(i=sum=0;i<n;i++)
        {
            for(j=0,ptr=root;s[i][j];j++)
            {
                while(ptr!=root && !ptr->c[to[s[i][j]]])
                    ptr=ptr->sub;
                if(ptr->c[to[s[i][j]]])
                    ptr=ptr->c[to[s[i][j]]];
                if(ptr->b<0)
                {
                    now[j]=0;
                    continue;
                }
                while(now[j]>0 && !c[ptr->b][now[j]])
                    now[j]=next[now[j]];
                if(c[ptr->b][now[j]])
                    now[j]++;
                if(now[j]==m)
                    sum++;
            }
        }
        printf("%d\n",sum);
    }
}
