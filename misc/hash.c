const int M=2011;
struct node
{
    int dat;
    struct node *ne;
};
typedef struct node node;
node *h[2011];
void ins(int x)
{
    int i=x%M;
    node *ptr=malloc(sizeof(*ptr));
    ptr->dat=x;
    ptr->ne=h[i];
    h[i]=ptr;
}
char find(int x)
{
    int i=x%M;
    node *ptr;
    for(ptr=h[i];ptr;ptr=ptr->ne)
        if(ptr->dat==x)return 1;
    return 0;
}
