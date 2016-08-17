#include<cstdio>
int m,u,v[1024],s[2][1024],q[2][1024];
void go(int now,int l,int *q,int *s,int& k,int i=0)
{
    if(v[now]!=u)
    {
        v[now]=u;
        s[now]=l;
        q[k++]=now;
    }
    int tmp;
    s[now]<?=l;
    for(;i<m;i++)
        if(now&(1<<i))
        {
            tmp=now,now&=~((1<<i)|(1<<(i+1)));
            go(now,l+1,q,s,k,i+2);
            now=tmp;
        }
}
main()
{
    int i,j,k,n,n1,T,now,tmp;
    char c[15];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        s[1-n%2][0]=q[1-n%2][0]=0,k=1;
        while(u++,n--)
        {
            scanf("%s",c);
            for(i=now=0;i<m;i++)
                now=now*2+(c[i]=='*');
            j=k,k=0;
            while(j--)
            {
                tmp=now;
                for(i=n1=0;i<m;i++)
                    if(q[n%2][j]&(1<<i))
                        n1++,tmp&=~(1<<i);
                n1+=s[n%2][q[n%2][j]];
                go(tmp,n1,q[1-n%2],s[1-n%2],k);
            }
        }
        printf("%d\n",s[1][0]);
    }
}
