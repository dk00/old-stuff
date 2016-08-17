#include<cstdio>
int v[99],c[99][99];
int go(int v)
{

}
main()
{
    int i,j,j,min,C=1;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        min=(n-1)*(n-2)/2;
        for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
                v[j]=0;
            j=go(i);
            if(j<min)min=j;
        }
        printf("Case #%d:\n%d\n\n",C++,min);
    }
}
