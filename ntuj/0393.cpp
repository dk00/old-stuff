#include<cstdio>
main()
{
    int i,j,k,n,m;
    char s1[999],s2[999];
    while(~scanf("%d %d",&n,&m))
    {
        for(i=0;i<m;i++)
            s1[i]=s2[i]=0;
        s1[0]=1;
        while(n--)
        {
            scanf("%d",&j);
            k=j%m;
            if(k<0)k+=m;
            j=m-k;
            for(i=0;i<m;i++)
                if(s1[i])
                    s2[(i+j)%m]=s2[(i+k)%m]=1;
            for(i=0;i<m;i++)
                s1[i]=s2[i],s2[i]=0;
        }
        puts(s1[0]?"Divisible":"Not divisible");
    }
}
