#include<cstdio>
main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<m;i++)
        {
            scanf("%d %d",&s[i].x,&s[i].y);
            if(s[i].x>s[i].y)
                swap(s[i].x,s[i].y);
        }
        scanf("%d",&x);
        while(x--)
        {
            scanf("%d %d",&j,&k);
            if(j>k)swap(j,k);
            for(i=0;i<m;i++)
                if((s[i].x==j && s[i].y==k)||(s[i].x==-j && s[i].y==-k))
                    s[i].x*=-1,s[i].y*=-1;
        }
    }
}
