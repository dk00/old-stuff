#include<cstdio>
struct node{char c,u;node *ch,*ne;}*root;
void ins(char a[],node *&ptr=root)
{
    if(!ptr)
    {
        ptr=new node;
        ptr->c=a[0];
        ptr->ne=ptr->ch=0;
        ptr->u=0;
    }
    if(ptr->c==a[0])
    {
        ptr->u++;
        if(a[1])ins(a+1,ptr->ch);
    }
    else ins(a,ptr->ne);
}
void find(char a[],node *ptr=root)
{
    if(ptr->c==a[0])
    {
        putchar(a[0]);
        if(ptr->u>1 && a[1])find(a+1,ptr->ch);
        else puts("");
    }
    else find(a,ptr->ne);
}
char s[1000][21];
main()
{
    int i,n;
    for(n=0;scanf("%s",s[n])>0;n++)
        ins(s[n]);
    for(i=0;i<n;i++)
        printf("%s ",s[i]),find(s[i]);
}
