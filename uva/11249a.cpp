#include<cstdio>
int s[21][100001];
main()
{
    int i,j,k,n,T;
    for(k=1;k<=20;k++)
        for(i=j=1;i<=100000;i++)
            if(!s[k][i])
            {
                if(i+j*(k+1)<=100000)
                    s[k][i+j*(k+1)]=i;
                s[k][i]=i+j++*(k+1);
            }
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&k,&n);
        while(n--)
        {
            scanf("%d %d",&i,&j);
            if(s[k][i<?j]==(i>?j))
                puts("LOSING");
            else
                puts("WINNING");
        }
        puts("");
    }
}
