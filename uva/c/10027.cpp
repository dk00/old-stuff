#include<cstdio>
struct node
{
    char x;
    node *ne,*ch,*ep;
};
void ins(node *&ptr,char a[])
{

}
void build(node *root,int n,char *s[])
{
    int i;
    for(i=0;i<n;i++)
        ins(root,s[i]);
}

main()
{
    int T;
    char tmp[99];
    scanf("*d%d",&T);
    printf("%d\n",T);
    while(T--)
    {
        scanf("\n*[\"]");
        
    }
}
