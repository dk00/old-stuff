#include<cstdio>
#include<cstring>
struct node
{
    node *ne,*ch;
    char d;
    int x;
}*root;
char num[]={2,2,2,3,3,3,4,4,1,1,5,5,6,6,0,7,0,7,7,8,8,8,9,9,9,0};
void clear(node *ptr=root)
{
    if(!ptr)return;
    clear(ptr->ne),clear(ptr->ch);
    delete ptr;
}
char ins(int i,char s[],node *&ptr=root)
{
    if(!ptr)
    {
        ptr=new node;
        ptr->d=num[s[0]-'a'];
        ptr->x=-1;
        ptr->ne=ptr->ch=NULL;
    }
    if(ptr->d!=num[s[0]-'a'])
        return ins(i,s,ptr->ne);
    if(!s[1])
    {
        if(ptr->x!=-1)return 0;
        ptr->x=i;
        return 1;
    }
    return ins(i,s+1,ptr->ch);
}
char word[50000][51];
int p[101],s[101];
void print(int i)
{
    if(i-strlen(word[p[i]])>0)
        print(i-strlen(word[p[i]])),putchar(' ');
    printf(word[p[i]]);
}
main()
{
    int i,j,k;
    char tmp[101],tmp0[51];
    node *ptr;
    while(scanf("%s",tmp) && tmp[0]!='-')
    {
        clear(),root=NULL;
        scanf("%d",&j);
        for(i=0;j--;)
        {
            scanf("%s",word[i]);
            for(k=0;word[i][k];k++)
                tmp0[k]=word[i][k];
            tmp0[k]=0;
            if(ins(i,tmp0))i++;
        }
        for(i=0;tmp[i];i++)s[i+1]=200000000;
        for(i=0;tmp[i];i++)
        {
            if(s[i]>=200000000)continue;
            for(j=0,ptr=root;ptr && tmp[i+j];j++,ptr=ptr->ch)
            {
                while(ptr && ptr->d!=tmp[i+j]-'0')ptr=ptr->ne;
                if(ptr && ptr->x>=0 && s[i]+1<s[i+j+1])
                    s[i+j+1]=s[i]+1,p[i+j+1]=ptr->x;
                if(!ptr)break;
            }
            
        }
        if(s[i]<200000000)
            print(i);
        else printf("No solution.");
        puts("");
    }
}
