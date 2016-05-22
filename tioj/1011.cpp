#include<cstdio>
main()
{
    int i,j,a,b;
    while(scanf("%d %d",&a,&b)==2)
    {
        for(i=0;a>>i;i++);
        for(j=0;b>>j;j++);
        if(i>j)a>>=(i-j),j=i-j;
        else b>>=(j-i),j-=i;
        for(i=0;a!=b;a/=2,b/=2,i++)
            i=i;
        printf("%d\n",i*2+j);
    }
}
