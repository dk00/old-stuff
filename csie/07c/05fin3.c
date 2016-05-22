struct node {
    int data;
    struct node *next;
};
struct node *merge_lists(struct node *a, struct node *b)
{
    if(!a)return b;
    if(!b)return a;
    if(a->data>b->data)
        return merge_lists(b,a);
    a->next=merge_lists(a->next,b);
    return a;
}
