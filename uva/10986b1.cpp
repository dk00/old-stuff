/*
�o�ذ��k�����Ƥ֪��Ϩӻ��O�ܦ��Ĳv��
�ӥB�A�Ω�]�t�t��(�����]�t�t��)����
*/
#include<cstdio>
struct Q
{
    int v,d;
}q[500000];
struct List
{
    int v,d;
    List *next;     //������Ъ������i�H�ۤv�ݡA��������
}*ptr,*tmp,*list[20000];    //�N�d�ѩΰݧ�
int d[20000];
main()
{
    int i,j,k,n,m,s,t,nv,nd,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d %d",&n,&m,&s,&t);
        for(i=0;i<n;i++)
        {
            d[i]=-1;
            if(!list[i])continue;
            for(ptr=list[i];ptr;)
            {
                tmp=ptr,ptr=ptr->next;
                delete tmp;
            }
            list[i]=0;
        }
        while(m--)
        {
            scanf("%d %d %d",&i,&j,&k);
            ptr=new List,*ptr=(List){j,k,0};
            if(!list[i])list[i]=ptr;
            else
            {
                ptr->next=list[i]->next;
                list[i]->next=ptr;
            }
            ptr=new List,*ptr=(List){i,k,0};
            if(!list[j])list[j]=ptr;
            else
            {
                ptr->next=list[j]->next;
                list[j]->next=ptr;
            }
        }
        q[0]=(Q){s,0};
        d[s]=0;
        for(i=0,j=1;i<j;i++)
        {
            nv=q[i].v,nd=q[i].d;
            if(nd>d[nv])continue;
            for(ptr=list[nv];ptr;ptr=ptr->next)
                if(d[ptr->v]<0 || nd+ptr->d<d[ptr->v])
                {
                    d[ptr->v]=nd+ptr->d;
                    q[j++]=(Q){ptr->v,nd+ptr->d};
                }
        }
        printf("Case #%d: ",C++);
        if(d[t]<0)puts("unreachable");
        else printf("%d\n",d[t]);
    }
}
