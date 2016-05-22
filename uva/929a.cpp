#include<cstdio>
struct list
{
    list *pre,*next;
    int x,y;
}*p[18000],*q[1000][1000];
list *ins(int x,int y,int d)
{
    list *ptr=new list;
    ptr->x=x,ptr->y=y;
    if(p[d])p[d]->pre=ptr;
    ptr->pre=NULL,ptr->next=p[d];
    return(p[d]=ptr);
}
list ext(int d)
{
    list tmp=*p[d],*ptr=p[d];
    p[d]=p[d]->next;
    if(p[d])p[d]->pre=NULL;
    delete ptr;
    return tmp;
}
void move(list *ptr,int d1,int d2)
{
    if(ptr->next)
        ptr->next->pre=ptr->pre;
    if(ptr->pre)
        ptr->pre->next=ptr->next;
    if(p[d1]==ptr)
        p[d1]=ptr->next;
    ptr->next=p[d2],p[d2]=ptr;
    ptr->pre=NULL,ptr->next->pre=ptr;
}
void clear()
{
    for(int i=0;i<18000;i++)
        while(p[i])ext(i);
}
const int inf=20000,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int s[1000][1000],d[1000][1000];
main()
{
    int i,j,nx,ny,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        clear();
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
            {
                scanf("%d",&s[i][j]);
                d[i][j]=inf;
            }
        i=d[0][0]=s[0][0];
        ins(0,0,s[0][0]);
        while(d[n-1][m-1]>=inf)
        {
            while(!p[i])i++;
            list nd=ext(i);
            for(j=0;j<4;j++)
            {
                nx=nd.x+dx[j],ny=nd.y+dy[j];
                if(nx>=0 && nx<n && ny>=0 && ny<m && i+s[nx][ny]<d[nx][ny])
                {
                    if(d[nx][ny]<inf)
                        move(q[nx][ny],d[nx][ny],i+s[nx][ny]);
                    else
                        q[nx][ny]=ins(nx,ny,i+s[nx][ny]);
                    d[nx][ny]=i+s[nx][ny];
                }
            }
        }
        printf("%d\n",d[n-1][m-1]);
    }
}
