#include<stdio.h>
#include<stdlib.h>
struct poly
{
    int c,e;
    poly *link;
};
poly *poly_add(poly *a,poly *b)
{
    if(a==NULL && b==NULL)
        return NULL;
        
    poly *ptr;
    ptr=new poly;
    
    if(b==NULL || (a!=NULL && a->e>b->e))
    {
        *ptr=*a;
        ptr->link=poly_add(a->link,b);
    }
    else if(a==NULL || (b!=NULL && b->e>a->e))
    {
        *ptr=*b;
        ptr->link=poly_add(a,b->link);
    }
    else
    {
        ptr->e=a->e;
        ptr->c=a->c+b->c;
        ptr->link=poly_add(a->link,b->link);
    }
    
    if(ptr->c!=0)
        return ptr;
    return ptr->link;
}
void poly_print(poly *a)
{
    printf("%d",abs(a->c));
    if(a->e>0)
        printf("x^%d",a->e);
        
    if(a->link!=NULL)
    {
        if(a->link->c>0)
            printf(" + ");
        else
            printf(" - ");
        poly_print(a->link);
    }
    else puts("");
}
main()
{
    poly *p,*q,*r,*s;
    
    p=new poly;
    *p=(poly){3,14,0};
    
    p->link=new poly;
    s=p->link;
    *s=(poly){2,8,0};
    
    s->link=new poly;
    s=s->link;
    *s=(poly){1,0,0};
    
    q=new poly;
    *q=(poly){8,14,0};
    
    q->link=new poly;
    s=q->link;
    *s=(poly){-3,10,0};
    
    s->link=new poly;
    s=s->link;
    *s=(poly){10,6,0};
    r=poly_add(p,q);
    poly_print(r);
    scanf(" ");
}
